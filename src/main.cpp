#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
class ScriptGenerator
{
public:
	ScriptGenerator(std::string input, std::string output);
	~ScriptGenerator();
	bool load();
	bool generate();

private:
	ScriptGenerator(const ScriptGenerator&) = delete;
	void operator=(const ScriptGenerator&) = delete;

	std::vector<std::vector<double>> _buffer;
	char _currentCharacter;
	std::string _line;
	std::ifstream _input;
	std::ofstream _output;

	void getData(size_t);
};

ScriptGenerator::ScriptGenerator(std::string input, std::string output)
{
	_input.open(input);
	_output.open(output);
}

ScriptGenerator::~ScriptGenerator()
{
	_input.close();
	_output.close();
}

bool ScriptGenerator::load()
{
	if (_input.is_open())
		{
			std::stringstream ss;

			if (!_input.get(_currentCharacter))
				{
					std::cout << "Empty!" << std::endl;
					return false;
				}
			while (_currentCharacter == '#')
				{
					getline(_input, _line);
					if (!_input.get(_currentCharacter))
						{
							std::cout << "EOF!" << std::endl;
							return false;
						}
				}
			while (_currentCharacter != '\n')
				{
					_buffer.push_back(std::vector<double>());
					getData(_buffer.size() - 1);

				}
			while (_input.get(_currentCharacter))
				{
					if (_currentCharacter == '#')
						{
							getline(_input, _line);
							continue;
						}
					for (uint32_t i = 0; i < _buffer.size(); i++)
						{
							if (_currentCharacter == ';')
								{
									_input.get(_currentCharacter);
									_input.get(_currentCharacter);
									continue;
								}
							getData(i);
						}
					if (_currentCharacter != '\n')
						getline(_input, _line);
				}

		}
	else
		{
			std::cout << "Can't open input!" << std::endl;
			return false;
		}
	std::cout << "Size: " << _buffer.size() << std::endl;
	return true;
}

void ScriptGenerator::getData(size_t i)
{
	for (int j = 0; j < 2; j++)
		{
			_line = "";
			while (_currentCharacter != ';' && _currentCharacter != '\n')
				{
					_line += _currentCharacter;
					_input.get(_currentCharacter);
				}
			double tmp;
			std::stringstream ss(_line);
			ss >> tmp;
			_buffer[i].push_back(tmp);
			if (_currentCharacter != '\n')
				_input.get(_currentCharacter);
		}
}

bool ScriptGenerator::generate()
{
	int32_t invert = 0;
	double scale;
	std::string numBuff;

	std::cout << "Invert?(y/n)" << std::endl;
	while (true)
		{
			std::cin >> numBuff;
			if (numBuff == "y" || numBuff == "Y")
				{
					invert = -1;
					break;
				}
			if (numBuff == "n" || numBuff == "N")
				{
					break;
				}
			std::cout << "Wrong answer! Try again." << std::endl;
		}

	std::cout << "Enter the scale value.( > 0)" << std::endl;
	while (true)
		{
			std::cin >> numBuff;
			if (numBuff.find_first_not_of("1234567890.-") != std::string::npos)
				{
					std::cout << "Invalid number: " << "\"" << numBuff << "\"! Try again." << std::endl;
					continue;
				}
			scale = atof(numBuff.c_str());
			if (scale <= 0)
				{
					std::cout << "Less than or equal to zero! Try again." << std::endl;
					continue;
				}
			break;
		}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if (_output.is_open())
		{
			_output << "(setq oldsnap (getvar \"osmode\"))" << std::endl << "Osmode 0" << std::endl;
			for (uint32_t i = 0; i < _buffer.size(); i++)
				{
					_output << "_PLINE" << std::endl;
					for (uint32_t j = 0; j < _buffer[i].size(); j += 2)
						{
							_output << std::fixed << _buffer[i][j + abs(invert)] << "," << std::fixed << _buffer[i][j + 1 + invert] << std::endl;
						}
					_output << std::endl;
					if (scale != 1)
						{
							_output << "_ZOOM" << std::endl << "_ALL" << std::endl << "_SCALE" << std::endl
							<< std::fixed << _buffer[i][0 + abs(invert)] << "," << std::fixed << _buffer[i][1 + invert] << std::endl
							<< std::endl << std::fixed << _buffer[i][0 + abs(invert)] << "," << std::fixed << _buffer[i][1 + invert] << std::endl
							<< std::fixed << scale << std::endl;
						}
				}
			_output << "(setvar \"osmode\" oldsnap)" << std::endl;
		}
	else
		{
			std::cout << "Can't create output!" << std::endl;
			return false;
		}
	return true;
}

int main()
{
	bool flag = true;
	while (flag)
		{
			ScriptGenerator *generator = new ScriptGenerator("input_vector.csv", "script.scr");
			if (!generator->load())
				{
					std::cout << "Can't load file!" << std::endl;
				}
			else if (generator->generate())
				{
					std::cout << "!!!Done!!!" << std::endl;
				}
			delete generator;
			std::cout << "\"Enter\" to exit or \"1\" to repeat." << std::endl;
			while (true)
				{
					char buffer;
					std::cin.get(buffer);
					if (buffer == '\n')
						{
							flag = false;
							break;
						}
					if (buffer == '1')
						{
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							break;
						}
				}
		}
    return 0;
}
