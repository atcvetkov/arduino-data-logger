const float shunt_resistor = 10.0;  // Твой шунт 10 Ом
const float reference_voltage = 5.0; // Опорное напряжение 5V для Nano
const int analog_pin = A0;  // Измеряем падение напряжения на A0

const int window_size = 10;  // Количество измерений для усреднения
float current_values[window_size] = {0};  // Массив для хранения значений
int index = 0;  // Индекс для массива

void setup() {
    Serial.begin(115200);
    Serial.println("ESP32 Power Consumption DataLogger - Started");
}

void loop() {
    int raw_value = analogRead(analog_pin);  // Читаем аналоговый вход (0-1023)
    float voltage = (raw_value / 1023.0) * reference_voltage; // Переводим в Вольты
    float current_mA = (voltage / shunt_resistor) * 1000; // Рассчёт тока (мА)

    // 🔹 Добавляем новое значение в массив
    current_values[index] = current_mA;
    index = (index + 1) % window_size;  // Двигаем индекс

    // 🔹 Рассчитываем среднее значение
    float sum = 0;
    for (int i = 0; i < window_size; i++) {
        sum += current_values[i];
    }
    float avg_current_mA = sum / window_size;  // Среднее значение

    // 🔥 Для Serial Plotter: Выводим два графика (мгновенное + среднее)
    Serial.print(current_mA);  
    Serial.print(" ");
    Serial.println(avg_current_mA);  

    delay(100); // Обновляем 10 раз в секунду
}