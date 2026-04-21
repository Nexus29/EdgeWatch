# 🚀 EdgeWatch — Real-Time Device Monitoring System

## 📌 Overview

**EdgeWatch** is a multi-layered monitoring system designed to simulate real-world industrial and IoT environments.

It demonstrates how to build a **high-performance C++ core**, integrate it with a **Qt/QML desktop interface**, and connect it to a **.NET backend API with database persistence**.

---

## 🧠 Architecture

```

[C++ Core Engine]
↓ (HTTP)
[ASP.NET Core API]
↓
[MariaDB]

[Qt/QML UI]

```

---

## 🧩 Components

### 🔧 C++ Core (`core-cpp/`)
- Device simulation (CPU, temperature, etc.)
- Multi-threaded processing
- Event system (alerts)
- Designed with SOLID principles
- No framework dependencies

---

### 🖥️ Qt Desktop UI (`qt-ui/`)
- Built with Qt6 and QML
- Real-time visualization of device data
- Alerts panel
- Uses Qt signals/slots for communication
- Clean separation via ViewModel layer

---

### 🌐 Backend API (`backend-dotnet/`)
- Built with ASP.NET Core Web API
- Receives data from C++ core
- Stores data in database
- Exposes endpoints for querying metrics

---

### 🗄️ Database
- MariaDB
- Stores:
  - Device metrics
  - Alerts

---

## 📁 Project Structure

```

EdgeWatch/
│
├── core-cpp/
│   ├── include/
│   ├── src/
│   ├── CMakeLists.txt
│
├── qt-ui/
│   ├── qml/
│   ├── viewmodels/
│   ├── main.cpp
│   ├── CMakeLists.txt
│
├── backend-dotnet/
│   └── EdgeWatch.Api/
│
├── shared/
│   ├── models/
│
├── README.md 
|
└── docker/

````

---

## ⚙️ Tech Stack

| Layer | Technology |
|------|-----------|
| Core | C++17/20 |
| UI | Qt6 + QML |
| Backend | ASP.NET Core |
| Database | MariaDB |
| Build | CMake + Ninja |

---

## 🔄 Data Flow

1. C++ Core generates device data
2. Data is processed and analyzed
3. Alerts are triggered if thresholds are exceeded
4. Data is sent via HTTP to backend API
5. Backend stores data in MariaDB
6. Qt UI displays real-time information

---

## 🚀 Getting Started

### 1. Clone repository
```bash
git clone <repo-url>
cd EdgeWatch
````

---

### 2. Build C++ Core

```bash
cd core-cpp
cmake -B build -G Ninja
cmake --build build
./build/core
```

---

### 3. Run Backend API

```bash
cd backend-dotnet/EdgeWatch.Api
dotnet run
```

---

### 4. Run Qt UI

```bash
cd qt-ui
cmake -B build
cmake --build build
./build/qt-ui
```
---

## 🎯 Why This Project

This project demonstrates:

* High-performance C++ development
* Modern Qt/QML UI design
* Backend API development with .NET
* Database integration
* Clean architecture and maintainability
