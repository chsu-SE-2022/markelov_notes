str := inttostr(Map.xlen)       +'|'+   //размер карты по ширине
       inttostr(Map.ylen)       +'|'+   //размер карты по длине
       floattostr(Map.stepx)    +'|'+   //масштаб карты по ширине
       floattostr(Map.stepy)    +'|'+   //масштаб карты по длине
       inttostr(Map.startx)     +'|'+   //начало данных на карте по ширине
       inttostr(Map.starty)     +'|'+   //начало данных на карте по длине
       inttostr(Map.lastx)      +'|'+   //конец данных на карте по ширине
       inttostr(Map.lasty)      +'|'+   // конец данных на карте по длине
       inttostr(Map.width)      +'|'+   //количество точек по ширине
       inttostr(Map.height)     +'|'+   //количество точек по длине
       floattostr(Map.level)    +'|';   //базовый уровень
       
Writeln(F, str);

str:=inttostr(len);

Writeln(F, str);  //длина заголовка

// Map contains single values
for i:=Map.starty to Map.lasty do
    BlockWrite(FT, Map.zmatrix[i][Map.startx], Map.width, bytes);
