# MQTT JSON API

## Топики

| Топик | Направление | Описание |
|-------|-------------|----------|
| `/Gomel/Tar/sensors/` | ESP32 → сервер | Данные сенсоров (каждые 30 сек) |
| `/Gomel/Tar/modules/` | сервер → ESP32 | Команды управления модулями |
| `/Gomel/Tar/response/` | ESP32 → сервер | Ответ на каждую команду |

---

## Данные сенсоров

ESP32 публикует на топик `topic_sensors` каждые 30 секунд:

```json
{
  "device_id": "A0001",
  "data": [
    { "SensorId": 1, "Type": "airTemperature",  "Value": 22.5, "Unit": "C"  },
    { "SensorId": 2, "Type": "airHumidity",     "Value": 58.3, "Unit": "%"  },
    { "SensorId": 3, "Type": "pressure",        "Value": 1013, "Unit": "Pa" },
    { "SensorId": 4, "Type": "plantHeight",     "Value": 12.4, "Unit": "cm" },
    { "SensorId": 5, "Type": "light",           "Value": 74.0, "Unit": "%"  },
    { "SensorId": 6, "Type": "soilTemperature", "Value": 20.1, "Unit": "C"  },
    { "SensorId": 7, "Type": "soilMoisture",    "Value": 45.0, "Unit": "%"  }
  ]
}
```

---

## Команды управления

Все команды отправляются на топик `topic_modules`.

### Общая структура

```json
{
  "device_id":  "A0001",
  "message_id": "<уникальный ID сообщения>",
  "type":       "<тип модуля>",
  "mode":       "<режим>",
  "action":     "<действие>",
  "schedule_unit": { ... }
}
```

### Типы модулей (`type`)

| Значение | Описание |
|----------|----------|
| `"led"` | Светодиод |
| `"dayLight"` | Основное освещение |
| `"uvLight"` | УФ-освещение |
| `"heater"` | Нагреватель |
| `"humidifier"` | Увлажнитель воздуха |
| `"fan"` | Вентилятор |
| `"waterPump"` | Насос полива |
| `"airFlap"` | Воздушная форточка (серво) |

---

## Установка режима

Поле `mode` содержит числовой код режима, `action` и `schedule_unit` не нужны.

| `mode` | Режим | Описание |
|--------|-------|----------|
| `0` | Off | Выключен |
| `1` | On | Включён постоянно |
| `2` | Weekly | По расписанию с учётом дня недели (`DD` = 01–07) |
| `3` | Daily | По расписанию каждый день (`DD` игнорируется) |

**Пример — включить нагреватель:**
```json
{
  "device_id":  "A0001",
  "message_id": "msg-001",
  "type":       "heater",
  "mode":       1
}
```

**Пример — перевести освещение в ежедневное расписание:**
```json
{
  "device_id":  "A0001",
  "message_id": "msg-002",
  "type":       "dayLight",
  "mode":       3
}
```

---

## Управление расписанием (ScheduleUnit)

Для операций с расписанием: `mode` = `4` (None), `action` = `"add"` или `"delete"`.

### Добавить единицу расписания

```json
{
  "device_id":  "A0001",
  "message_id": "msg-003",
  "type":       "dayLight",
  "mode":       4,
  "action":     "add",
  "schedule_unit": {
    "schedule_unit_id": "01JKY5E122HBQSZKXMF0F7HR44",
    "kind":     "power",
    "interval": {
      "start": "01T06:00",
      "end":   "07T22:00"
    },
    "quantity": {
      "magnitude": 80,
      "unit": 1
    }
  }
}
```

### Удалить единицу расписания

```json
{
  "device_id":  "A0001",
  "message_id": "msg-004",
  "type":       "dayLight",
  "mode":       4,
  "action":     "delete",
  "schedule_unit": {
    "schedule_unit_id": "01JKY5E122HBQSZKXMF0F7HR44"
  }
}
```

---

## Формат ScheduleUnit

### Поле `kind`

| Значение | Описание |
|----------|----------|
| `"power"` | Задать мощность напрямую (`magnitude` = 0–100%) |
| `"prefer"` | Поддерживать параметр среды (`magnitude` = целевое значение) |

> `"prefer"` недоступен для `led`, `fan`, `airFlap` — игнорируется.

### Поле `interval` — формат времени `"DDThh:mm"`

| Часть | Описание |
|-------|----------|
| `DD` | День недели: `01`=пн, `02`=вт, `03`=ср, `04`=чт, `05`=пт, `06`=сб, `07`=вс |
| `hh` | Час (00–23) |
| `mm` | Минута (00–59) |

> В режиме **Daily** (`mode: 3`) поле `DD` игнорируется — интервал повторяется каждый день.  
> В режиме **Weekly** (`mode: 2`) `DD` обязателен: `01`–`07`.

### Поле `quantity`

| Поле | Тип | Описание |
|------|-----|----------|
| `magnitude` | int | Значение (0–100 для процентов, градусы для температуры) |
| `unit` | int | `1`=%, `2`=количество, `3`=°C |

---

## Ответ (`topic_response`)

На каждую команду ESP32 отвечает:

```json
{
  "device_id":  "A0001",
  "message_id": "msg-003",
  "code":       2
}
```

### Коды ответа

| Код | Описание |
|-----|----------|
| `2` | Успешно: ScheduleUnit добавлен или удалён |
| `1` | Успешно: режим установлен |
| `-1` | Ошибка: не удалось установить режим |
| `-2` | Ошибка: не удалось изменить ScheduleUnit (не найден, расписание заполнено, неизвестный action) |
| `-3` | Ошибка: неверный `device_id` |
| `-4` | Ошибка: JSON не распарсился |

---

## Лимиты расписания

| Модуль | Макс. ScheduleUnit |
|--------|-------------------|
| dayLight, uvLight | 12 |
| heater, humidifier, airFlap | 10 |
| led, fan, waterPump | 4 |

---

## Примеры

### Нагреватель: поддерживать 22°C с пн по пт с 6:00 до 22:00 (Weekly)

```json
{
  "device_id": "A0001", "message_id": "msg-010",
  "type": "heater", "mode": 4, "action": "add",
  "schedule_unit": {
    "schedule_unit_id": "unit-heater-1",
    "kind": "prefer",
    "interval": { "start": "01T06:00", "end": "05T22:00" },
    "quantity": { "magnitude": 22, "unit": 3 }
  }
}
```

### Полив: каждый день 5 минут в 8:00 на 70% мощности (Daily)

```json
{
  "device_id": "A0001", "message_id": "msg-011",
  "type": "waterPump", "mode": 4, "action": "add",
  "schedule_unit": {
    "schedule_unit_id": "unit-pump-1",
    "kind": "power",
    "interval": { "start": "01T08:00", "end": "01T08:05" },
    "quantity": { "magnitude": 70, "unit": 1 }
  }
}
```

> Режим Daily — поле `DD` игнорируется при проверке расписания. В примере выше использован `01`, но значение роли не играет.

### Перевести насос в режим Daily и выключить увлажнитель

```json
{ "device_id": "A0001", "message_id": "msg-012", "type": "waterPump",  "mode": 3 }
```
```json
{ "device_id": "A0001", "message_id": "msg-013", "type": "humidifier", "mode": 0 }
```
