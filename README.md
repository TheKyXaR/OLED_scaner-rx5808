![image](https://github.com/user-attachments/assets/2a631d49-d21c-451d-a9e1-731b9f949554)# OLED Сканер RX5808

Проект створення OLED сканера з використанням модуля RX5808. Цей сканер розроблений для компактного, ефективного та зручного використання, забезпечуючи чітке та точне сканування частот.

## Особливості

- **Висока точність**: Використовує модуль RX5808 для точного сканування частот.
- **OLED дисплей**: Чіткий і яскравий дисплей для легкого зчитування інформації.
- **Компактний дизайн**: Портативний і зручний у використанні.

## Вимоги

- Плата Arduino (наприклад, Arduino Uno)
- Модуль RX5808
- OLED дисплей
- Провідники (jumper wires)
- Макетна плата (необов'язково для прототипування)

## Встановлення

1. **Клонуйте репозиторій**:
    ```sh
    git clone https://github.com/TheKyXaR/OLED_scaner-rx5808.git
    ```
2. **Встановіть необхідні бібліотеки**:
    Переконайтеся, що у вашій Arduino IDE встановлені такі бібліотеки:
    - **Adafruit GFX Library**
    - **Adafruit SSD1306**
    - **SPI Library**

3. **Завантажте код**:
    Відкрийте файл `OLED_scanner_rx5808.ino` в Arduino IDE та завантажте його на вашу плату Arduino.

## Використання

1. **Підключіть модуль RX5808 та OLED дисплей до вашої плати Arduino** згідно зі схемою з'єднань.
![image](https://github.com/user-attachments/assets/7594f2ad-9b20-45f0-b0e9-b8105c08cf83)
2. **Увімкніть вашу плату Arduino**.
3. **Слідкуйте за OLED дисплеєм** для результатів сканування частот.

## Внесок

1. Форкніть репозиторій.
2. Створіть свою гілку з новою функцією (`git checkout -b feature/AmazingFeature`).
3. Зробіть коміт ваших змін (`git commit -m 'Додати нову функцію AmazingFeature'`).
4. Запуште в гілку (`git push origin feature/AmazingFeature`).
5. Відкрийте pull request.

## Ліцензія

Цей проект ліцензовано за ліцензією MIT. Деталі дивіться у файлі [LICENSE](LICENSE).

## Вдячності

- Цей проект був реалізований під чуйним керівництвом людей з компанії Renesas Electronics.
- Особлива подяка авторам бібліотек, використаних у цьому проекті.
- Натхнення для створення компактного та ефективного сканера частот.
