# Сенсоры

> _Документ сгенерирован с помощью ИИ. При расхождении с поведением прошивки приоритет за кодом._

Сенсоры регистрируются в `setup()` через `info.addSensorInfo(...)`. Данные публикуются в MQTT каждые 30 секунд.

---

## Регистрация сенсора в коде

```cpp
// setup() в main.cpp
info.addSensorInfo(SensorInfo(1, "airTemperature", "C",  readTemperatureBME));
info.addSensorInfo(SensorInfo(4, "plantHeight",    "cm", readPlantHeight));
```

Аргументы `SensorInfo`:

| Аргумент | Описание |
|---|---|
| `SensorId` | Числовой идентификатор в MQTT JSON |
| `Type` | Строковый тип (передаётся в MQTT as-is) |
| `Unit` | Единица измерения (передаётся в MQTT as-is) |
| `function` | Функция чтения, возвращает `float` |

---

## Список сенсоров

| SensorId | Type | Unit | Описание | Аппаратура | Пин |
|---|---|---|---|---|---|
| — | `randomNumber` | `-` | Случайное число для тестирования MQTT | — | — |
| 1 | `airTemperature` | `C` | Температура воздуха | BME280 | I2C |
| 2 | `airHumidity` | `%` | Влажность воздуха | BME280 | I2C |
| 3 | `pressure` | `Pa` | Атмосферное давление | BME280 | I2C |
| 4 | `plantHeight` | `cm` | Высота растения | HC-SR04 (УЗ) | TRIG=33, ECHO=25 |
| 5 | `light` | `%` | Освещённость | Фоторезистор | GPIO 34 |
| 6 | `soilTemperature` | `C` | Температура почвы | NTC термистор | GPIO 35 |
| 7 | `soilMoisture` | `%` | Влажность почвы | Ёмкостный датчик | GPIO 32 |

> `randomNumber` используется вместо реальных сенсоров для проверки MQTT-соединения.  
> Активные сенсоры определяются вызовами `addSensorInfo()` в `setup()`.

---

## Высота растения

Вычисляется как:

```
plantHeight = CONTAINER_DEPTH_CM − расстояние_от_сенсора
```

Константа `CONTAINER_DEPTH_CM` задаётся в `main.cpp` (по умолчанию `35.0` см). При аномальном показании датчика возвращается `0`.

---

## Формат данных в MQTT

Сенсорные данные публикуются в топик `topic_sensors`. Подробнее — в [MQTT_API.md](MQTT_API.md#3-данные-сенсоров).
