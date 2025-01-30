#include <IRremote.h>

// Определяем пины для светодиодов
const int redLed = 8;      
const int yellowLed = 9;   
const int greenLed = 10;   
const int greenLedLeft = 11;  
const int greenLedRight = 12;  

long number = 99; 

// Пин ИК-приемника
const int irPin = 2;

// Пин кнопки
const int buttonPin = A3;

IRrecv irrecv(irPin);  // ИК приемник

int tens_digit = 0;   
int units_digit = 0;  

int CA_1 = A4; 
int CA_2 = A5; 
int clk = 6;   
int latch = 5; 
int data = 4;  

int count = 0; 
int digits[2]; 
int CAS[2] = {A4, A5}; 

byte numbers[12] = {
  B00000011, 
  B10011111, 
  B00100100, 
  B00001100, 
  B10011000, 
  B01001000, 
  B01000000, 
  B00011111, 
  B00000000, 
  B00001000,  
  B11111110,  // 10: прочерк (-)
  B11111111  // 11 (ничего)
};

unsigned long previousMillis = 0;
unsigned long phaseStartTime = 0;
unsigned long ledSwitchTime = 0; 

const unsigned long redPhaseTime = 18000;  
const unsigned long greenPhaseTime = 21000; 
const unsigned long yellowPhaseTime = 2000; 
const unsigned long redYellowPhaseTime = 2000; 
const unsigned long ledBlinkInterval = 1000;  

unsigned long phaseStartTime3 = 0;  // Время начала текущей фазы
unsigned long countdownTime = 15000;  // Время обратного отсчёта
unsigned long yellowTime = 2000;      // Время жёлтого света
unsigned long blinkInterval = 500;    // Интервал мигания зелёных
unsigned long dashBlinkTime = 500;  // Время мигания (мс)
unsigned long lastDashBlink = 0;    // Время последнего мигания
bool dashState = false;             // Состояние мигания (показывать или не показывать прочерки)
bool countdownActive = false;  // Активен ли таймер
bool buttonPressed = false;    // Нажата ли кнопка

int currentPhase = 0; 
int innerState = 0; 

int currentMode = 0;  // 0 - нет режима, 1 - режим 1, 2 - режим 2

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLedLeft, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(greenLedRight, OUTPUT);

  pinMode(CA_1, OUTPUT);
  pinMode(CA_2, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 
  
  irrecv.enableIRIn();

  digitalWrite(CA_1, HIGH);
  digitalWrite(CA_2, HIGH);

  phaseStartTime = millis();
  break_number(number);
}

void loop() {
  if (irrecv.decode()) {  // Чтение данных с пульта
    unsigned long value = irrecv.decodedIRData.command;  // Получаем команду напрямую

    // Используем полученную команду в switch
    switch (value) {
      case 12:  // Код кнопки "1"
        clear();
        currentMode = 1;  // Переключаемся в режим 1
        break;
      case 24:  // Код кнопки "2"
        clear(); 
        currentMode = 2;  // Переключаемся в режим 2
        break;
      case 94:  // Код кнопки "3"
        clear();
        resetToGreen();  // Устанавливаем начальное состояние (все зелёные горят)
        currentMode = 3;  // Переключаемся в режим 3
        break;
      case 8:  // Код кнопки "4"
        clear();
        currentMode = 4;  // Переключаемся в режим 4
        break;
      case 67:
        clear();
        digitalWrite(CA_1, 0);
        digitalWrite(CA_2, 0);
        currentMode = 0;  // Переключаемся в режим 0
        break;
    }

    irrecv.resume();  // Подготовка к следующему сигналу
  }

  // Выполняем действия в зависимости от текущего режима
  if (currentMode == 1) {
    mode1();  // Включаем режим 1
  } else if (currentMode == 2) {
    mode2();  // Включаем режим 2
  } else if (currentMode == 3) {
    mode3();  // Включаем режим 3
  } else if (currentMode == 4) {
    mode4();  // Включаем режим 4
  }
}

void mode1() {
  unsigned long currentMillis = millis();

  // Обновляем разряды дисплея (только если не жёлтая или красно-жёлтая фаза)
  if (currentPhase != 1 && currentPhase != 3) {
    if (currentMillis - previousMillis >= 5) {
      previousMillis = currentMillis;
      display_number();
    }
  } else {
    clearDisplay(); // Очищаем дисплей на жёлтой и красно-жёлтой фазах
  }

  // Управление фазами
  switch (currentPhase) {
    case 0: // Красный
      if (currentMillis - phaseStartTime >= redPhaseTime) {
        phaseStartTime = currentMillis;
        currentPhase = 1;
        innerState = 0;
      }
      handleRedPhase(currentMillis);
      break;

    case 1: // Красный + жёлтый
      if (currentMillis - phaseStartTime >= redYellowPhaseTime) {
        phaseStartTime = currentMillis;
        currentPhase = 2;
        innerState = 0;
      }
      switchToRedYellow();
      break;

    case 2: // Зелёный
      if (currentMillis - phaseStartTime >= greenPhaseTime) {
        phaseStartTime = currentMillis;
        currentPhase = 3;
        innerState = 0;
      }
      handleGreenPhase(currentMillis);
      break;

    case 3: // Жёлтый
      if (currentMillis - phaseStartTime >= yellowPhaseTime) {
        phaseStartTime = currentMillis;
        currentPhase = 0;
        innerState = 0;
      }
      switchToYellow();
      break;
  }

  // Таймер обратного отсчёта (не обновляется на жёлтой и красно-жёлтой фазах)
  if (currentPhase != 1 && currentPhase != 3) {
    // Добавляем 1 секунду к оставшемуся времени
    unsigned long remainingTime = (phaseStartTime + getPhaseTime(currentPhase) - currentMillis) / 1000 + 1;
    updateTimerDisplay(remainingTime);
  }
}

void mode2() {
  digitalWrite(CA_1, 0);
  digitalWrite(CA_2, 0);
  if (irrecv.decode()) {  // Чтение данных с пульта
    unsigned long value = irrecv.decodedIRData.command;  // Получаем команду напрямую

    // Используем полученную команду в switch
    switch (value) {
      case 28:  // Код кнопки "5" (пример)
        activateRed();
        break;
      case 90:  // Код кнопки "6" (пример)
        activateYellow();
        break;
      case 66:  // Код кнопки "7" (пример)
        activateGreen();
        break;
      case 82:  // Код кнопки "8" (пример)
        activateGreenLeft();
        break;
      case 74:  // Код кнопки "9" (пример)
        activateGreenRight();
        break;
      default:
        Serial.println("Неизвестная команда");
        break;
    }

    irrecv.resume();  // Подготовка к следующему сигналу
  }
}

void mode3() {
  unsigned long currentMillis = millis();

  if (digitalRead(buttonPin) == LOW && !buttonPressed) {
    buttonPressed = true;
    countdownActive = true;
    phaseStartTime3 = currentMillis;
    currentPhase = 0;
  }

  if (countdownActive) {
    switch (currentPhase) {
      case 0: // Обратный отсчёт 15 секунд
        handleCountdown(currentMillis);
        break;
      case 1: // Жёлтый (2 секунды)
        if (currentMillis - phaseStartTime3 >= yellowTime) {
          currentPhase = 2;
          phaseStartTime3 = currentMillis;
          switchToRed();
        }
        break;
      case 2: // Красный + таймер
        handleRedPhase3(currentMillis);
        break;
      case 3: // Красный + жёлтый (2 секунды)
        if (currentMillis - phaseStartTime3 >= yellowTime) {
          resetToGreen();
          countdownActive = false;
          buttonPressed = false;
        }
        break;
    }
  } else {
    // Если таймер не активен, показываем прочерки
    displayDashes();
  }
}

void mode4() {
  digitalWrite(yellowLed, HIGH);  // Включаем светодиод
  delay(500);  // Задержка 500 мс (светодиод включен)
  digitalWrite(yellowLed, LOW);   // Выключаем светодиод
  delay(500);  // Задержка 500 мс (светодиод выключен)
}

void handleRedPhase(unsigned long currentMillis) {
  if (innerState == 0) {
    switchToRed();
    if (currentMillis - phaseStartTime >= 5000) { // Через 5 секунд включаем левую стрелку
      innerState = 1;
      ledSwitchTime = currentMillis;
    }
  } else if (innerState == 1) {
    digitalWrite(greenLedLeft, HIGH);
    if (currentMillis - ledSwitchTime >= 5000) { // 5 секунд горит стрелка
      innerState = 2;
      ledSwitchTime = currentMillis;
    }
  } else if (innerState == 2) {
    if ((currentMillis - ledSwitchTime) % ledBlinkInterval < ledBlinkInterval / 2) {
      digitalWrite(greenLedLeft, HIGH);
    } else {
      digitalWrite(greenLedLeft, LOW);
    }
    if (currentMillis - ledSwitchTime >= 3000) { // 3 секунды мигает стрелка
      innerState = 3;
    }
  } else if (innerState == 3) {
    switchToRed();
  }
}

void handleRedPhase3(unsigned long currentMillis) {
  unsigned long timeLeft = countdownTime - (currentMillis - phaseStartTime3);

  if (timeLeft <= 0) {
    currentPhase = 3;
    phaseStartTime3 = currentMillis;
    switchToRedYellow();
    clearDisplay();
    return;
  }

  updateTimerDisplay3((timeLeft / 1000) + 1);
}

void handleGreenPhase(unsigned long currentMillis) {
  if (innerState == 0) { // Зелёный свет без стрелки
    switchToGreen();
    if (currentMillis - phaseStartTime >= 5000) { 
      innerState = 1;
      ledSwitchTime = currentMillis;
    }
  } 
  else if (innerState == 1) { // Зелёный свет + правая стрелка
    digitalWrite(greenLedRight, HIGH);
    if (currentMillis - ledSwitchTime >= 5000) { 
      innerState = 2;
      ledSwitchTime = currentMillis;
    }
  } 
  else if (innerState == 2) { // Зелёный свет + мигающая правая стрелка
    if ((currentMillis - ledSwitchTime) % ledBlinkInterval < ledBlinkInterval / 2) {
      digitalWrite(greenLedRight, HIGH);
    } else {
      digitalWrite(greenLedRight, LOW);
    }
    if (currentMillis - ledSwitchTime >= 3000) { 
      innerState = 3;
      ledSwitchTime = currentMillis;
    }
  } 
  else if (innerState == 3) { // Зелёный свет без стрелки
    digitalWrite(greenLedRight, LOW);
    switchToGreen();
    if (currentMillis - ledSwitchTime >= 5000) { 
      innerState = 4;
      ledSwitchTime = currentMillis;
    }
  } 
  else if (innerState == 4) { // Мигание зелёного света
    if ((currentMillis - ledSwitchTime) % ledBlinkInterval < ledBlinkInterval / 2) {
      digitalWrite(greenLed, HIGH);
    } else {
      digitalWrite(greenLed, LOW);
    }
    if (currentMillis - ledSwitchTime >= 3000) { 
      innerState = 5;
    }
  } 
  else if (innerState == 5) { // Завершение фазы зелёного
    switchToGreen(); // Вернуть обычный зелёный свет перед окончанием
  }
}

unsigned long getPhaseTime(int phase) {
  switch (phase) {
    case 0: return redPhaseTime;
    case 1: return redYellowPhaseTime;
    case 2: return greenPhaseTime;
    case 3: return yellowPhaseTime;
  }
  return 0;
}

void break_number(long num) {
  digits[0] = num / 10;
  digits[1] = num % 10;
}

void display_number() {
  // Отключаем текущий катод перед включением нового
  digitalWrite(CAS[count], HIGH);

  // Отправляем данные в сдвиговый регистр
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, numbers[digits[count]]);
  digitalWrite(latch, HIGH);

  // Включаем новый катод
  digitalWrite(CAS[count], LOW);

  // Переходим к следующему разряду
  count++;
  if (count == 2) count = 0;
}


void cathode_high() {
  digitalWrite(CA_1, HIGH);
  digitalWrite(CA_2, HIGH);
}

void switchToRed() {
  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(greenLedLeft, LOW);
  digitalWrite(greenLedRight, LOW);
}

void switchToRedYellow() {
  digitalWrite(redLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(greenLedLeft, LOW);
  digitalWrite(greenLedRight, LOW);
}

void switchToGreen() {
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);
  digitalWrite(greenLedLeft, LOW);
  digitalWrite(greenLedRight, LOW);
}

void switchToYellow() {
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(greenLedLeft, LOW);
  digitalWrite(greenLedRight, LOW);
}

void activateRed() {
  clearAll();
  digitalWrite(redLed, HIGH);
}

void activateYellow() {
  clearAll();
  digitalWrite(yellowLed, HIGH);
}

void activateGreen() {
  clearAll();
  digitalWrite(greenLed, HIGH);
}

void activateGreenLeft() {
  // Проверяем текущее состояние пина и меняем его
  if (digitalRead(greenLedLeft) == HIGH) {
    digitalWrite(greenLedLeft, LOW);  // Если включен — выключаем
  } else {
    digitalWrite(greenLedLeft, HIGH); // Если выключен — включаем
  }
  delay(200);  // Задержка 200 мс между нажатиями
}

void activateGreenRight() {
  // Проверяем текущее состояние пина и меняем его
  if (digitalRead(greenLedRight) == HIGH) {
    digitalWrite(greenLedRight, LOW);  // Если включен — выключаем
  } else {
    digitalWrite(greenLedRight, HIGH); // Если выключен — включаем
  }
  delay(200);  // Задержка 200 мс между нажатиями
}

void handleCountdown(unsigned long currentMillis) {
  unsigned long timeLeft = countdownTime - (currentMillis - phaseStartTime3);

  if (timeLeft <= 0) {
    currentPhase = 1;
    phaseStartTime3 = currentMillis;
    switchToYellow();
    clearDisplay();
    return;
  }

  // Мигание зелёных за последние 3 секунды
  if (timeLeft <= 3000 && (timeLeft / blinkInterval) % 2 == 0) {
    digitalWrite(greenLed, LOW);
    digitalWrite(greenLedLeft, LOW);
    digitalWrite(greenLedRight, LOW);
  } else {
    digitalWrite(greenLed, HIGH);
    digitalWrite(greenLedLeft, HIGH);
    digitalWrite(greenLedRight, HIGH);
  }

  updateTimerDisplay3((timeLeft / 1000) + 1);
}

void resetToGreen() {
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);
  digitalWrite(greenLedLeft, HIGH);
  digitalWrite(greenLedRight, HIGH);
  countdownActive = false;  // Деактивируем таймер
  displayDashes();  // Отображаем прочерки
}

void updateTimerDisplay3(unsigned long timeLeft) {
  if (!countdownActive) return; // Если таймер не активен, ничего не обновляем

  break_number(timeLeft);  // Разделяем число на разряды

  // Отключаем текущий катод перед включением нового
  digitalWrite(CAS[count], HIGH);

  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, numbers[digits[count]]); // Выводим цифру на сегменты
  digitalWrite(CAS[count], LOW);  // Включаем нужный катод (только один)
  digitalWrite(latch, HIGH);

  count++;
  if (count == 2) count = 0; // Сбрасываем счётчик разрядов
}

void displayDashes() {
  unsigned long currentMillis = millis();

  // Проверяем, пора ли менять состояние мигания
  if (currentMillis - lastDashBlink >= dashBlinkTime) {
    dashState = !dashState;  // Меняем состояние мигания
    lastDashBlink = currentMillis;  // Обновляем время последнего мигания
  }

  if (dashState) {
    // Отображаем прочерки
    digits[0] = 10;  // Прочерк
    digits[1] = 10;  // Прочерк
  } else {
    // Если не мигаем, выключаем сегменты
    digits[0] = 11;  // Ничего
    digits[1] = 11;  // Ничего
  }

  // Отключаем текущий катод перед включением нового
  digitalWrite(CAS[count], HIGH);

  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, numbers[digits[count]]); // Выводим цифру или прочерк
  digitalWrite(CAS[count], LOW);  // Включаем нужный катод (только один)
  digitalWrite(latch, HIGH);

  count++;
  if (count == 2) count = 0; // Сбрасываем счётчик разрядов
}

void clearAll() {
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
}

void clear() {
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(greenLedLeft, LOW);
  digitalWrite(greenLedRight, LOW);
}

void clearDisplay() {
  digitalWrite(CA_1, 0); // Отключить первый разряд
  digitalWrite(CA_2, 0); // Отключить второй разряд
}

void updateTimerDisplay(unsigned long timeLeft) {
  break_number(timeLeft);
}
