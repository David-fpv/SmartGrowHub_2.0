# LittleFS — хранение настроек

> _Документ сгенерирован с помощью ИИ. При расхождении с поведением прошивки приоритет за кодом._

ESP32 хранит два типа файлов на LittleFS: конфигурацию подключения и состояние модулей.

---

## config.json — WiFi и MQTT

Файл находится в папке `data/` и загружается на устройство вручную.

```json
{
  "ssid":              "MyNetwork",
  "password":          "mypassword",
  "server":            "broker.emqx.io",
  "port":              1883,
  "user":              "",
  "mqtt_pass":         "",
  "topic_sensors":     "/Gomel/Tar/sensors/",
  "topic_modules":     "/Gomel/Tar/modules/",
  "topic_response":    "/Gomel/Tar/response/",
  "max_wifi_attempts": 20,
  "max_mqtt_attempts": 10,
  "mqtt_buffer_size":  1000,
  "utc_offset_sec":    10800
}
```

Если файл отсутствует — используются значения по умолчанию из `main.cpp`.

### Загрузка через VS Code (PlatformIO)

1. Открыть боковую панель PlatformIO (иконка муравья слева)
2. **PROJECT TASKS → pico32 → Platform → Upload Filesystem Image**

Или через терминал:

```bash
pio run --target uploadfs
```

> Загрузка перезапишет весь LittleFS, включая сохранённые настройки модулей.

---

## \<module\>.json — настройки модулей

Создаются и обновляются **автоматически** при каждом изменении через MQTT. Один файл на модуль: `led.json`, `dayLight.json`, `heater.json` и т.д.

Настройки восстанавливаются после перезапуска без участия сервера.

### Формат (внутренний, не для ручного редактирования)

```json
{
  "mode": 3,
  "schedule": [
    {
      "id":   "01JKY5E122HBQSZKXMF0F7HR44",
      "kind": 0,
      "d1": 1, "h1": 6,  "m1": 0,
      "d2": 5, "h2": 22, "m2": 0,
      "mag":  80,
      "unit": 1
    }
  ]
}
```

---

## Просмотр состояния

При каждом старте ESP32 выводит в Serial Monitor состояние всех зарегистрированных модулей:

```
=== modules (2) ===
  [1] led           mode=off      schedule=0/4
  [2] dayLight      mode=weekly   schedule=1/12
       01JKY5E122HBQSZKXMF0F7HR44  power   01T06:00 -> 05T22:00  80%
===================
```

---

## Лимиты

Все настройки занимают не более **~10 KB** при полном заполнении всех расписаний. LittleFS на ESP32 с 4 МБ flash предоставляет **~1.4 МБ** — запас более чем достаточный.
