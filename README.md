# acadScript
Генерирует autocad-скрипт для построения _PLINE по точкам.<br>
На вход принимает input_vector.csv, на выход генерирует script.scr.<br>
Пример .csv файла сгенерированного с помощью excel:<br>
0;-4;-1.6;0;3.5;0<br>
7;-6.5;-1.6;14;3.5;13.5<br>
10.5;-15;-15.9;14;9.8;21.3<br>
7.5;-23.2;-15.9;0.2;15.4;13.6<br>
0.5;-26.8;-13.4;0.2;15.4;0.1<br>
-5.8;-25;-13.4;2.3;3.5;0<br>
-9.5;-19;-11.7;7.8;9.6;13.5<br>
-10.8;-12.8;-8.7;9.8;15.4;0.1<br>
-7.4;-7.7;-5.4;8.1;6.55;6.8<br>
0;-4;-4;2.5;12.5;6.8<br>
;;-4;0;3.5;0<br>
;;-1.6;0;11;3.4<br>
;;;;11;0.05<br>
;;;;7.2;1.7<br>
;;;;7.2;0<br>
Если первым символом строки будет '#' строка не считывается.<br>
Координаты точек задаются столбцами (x,y).<br>
Первая читаемая строка используется для определения количества столбцов.<br>
Первая читаемая строка может заканчиваться только переносом строки или ';'.<br>
Первая координата используется в качестве опорной точки для масштабирования.<br>
Программа может инвертировать x,y.<br>
