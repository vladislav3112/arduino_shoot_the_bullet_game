##Проект на ardoino one
Игра  shoot the bullet(#2), пример:	https://www.microsoft.com/en-us/p/brick-game-simulator/9nblggh4qfmw  
Здесь содержатся(или будут позже) две версии: консольное демо(test)  
и финальная версия для arduino one  + lcd5110 + joystik shield.  

#Заметки по консольной версии:
Нужно растянуть консоль на весь экран(48*84 клетки, поле может не поместиться)  

#Логика:
class gameField для описания игрового поля, class Player - игрок, унаследован от gameField,  
код в файлах GameField.cpp и GameField.h.  
Также основной файл shoot_the_bullet.cpp(.ino в финальной версии), где обрабатывается вывод на экран.  

#Запуск:
1.Подключение через usb к компьютеру:   
  joystik shield-nokia (напрямую) lcd : pins:   
    rst<->d13;  
    ce<->d12;  
    ...  
    light<->key  
  joystik shield-arduino one (напрямую) lcd : pins:   
    3v3<->aref;  
    gnd<->gnd;  
    d13<->d13  
    ...  
    7-0<->V,A,A,E,K,X  
 
 2.
 управление:  
 E - огонь;  
 D - влево;  
 B - вправо;  
 
 3. 
 
 ...                             ...                       ... 
  .    //нерушимый блок          . .  //рушимый блок        .     //игрок
 ...                             ...                       ...
