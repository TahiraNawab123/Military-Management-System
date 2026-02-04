## Military Management System

A C++-based, console-driven **Military Management System** that simulates a command-center style dashboard for managing:

- **User accounts & roles** (Admin, Officer, Soldier)
- **Operational issue reporting & approval workflow**
- **Intrusion Detection System (IDS)** with sensors and threat levels
- **Equipment inventory management** with maintenance tracking
- **Secure communication & logging** using Caesar cipher
- **Alerting system** with email/SMS-style alerts and JSON persistence

All modules are integrated into a single main menu and can also be tested individually.

---

## Features & Modules

- **Role-Based Access Control**
  - **Admin**
    - Manage user accounts (`add`, `modify`, `delete`)
    - Reset passwords
    - View user distribution reports (Admins/Officers/Soldiers)
  - **Officer**
    - View all reported issues
    - Approve or update issue statuses (e.g., Pending, In Progress, Resolved)
    - View IDS events, alerts, and inventory summaries (via dedicated menus)
  - **Soldier**
    - Report issues (ID, title, description, status)
    - View their reported issues and statuses

- **Messaging System**
  - Send messages between users
  - View inbox (messages received for a username)
  - Edit previously sent messages

- **Intrusion Detection System (IDS)**
  - `MotionSensor` and `HeatSensor` implementations
  - `SensorInventory` to add/remove/search sensors
  - `Intruder` and `IntrusionLog` with JSON reporting
  - Threat analysis (`LOW`, `MEDIUM`, `HIGH`) with audible beeps (Windows `Beep`)

- **Equipment Inventory**
  - Add / remove equipment items
  - Optional maintenance records (last service date, status)
  - Save and load inventory as JSON
  - Check for existence of equipment by ID

- **Secure Communication**
  - `CaesarEncryption` implementing an `Encryption` interface
  - `SecureMessage` for encrypt/decrypt/retry send flows
  - `LogManager` (singleton) writing communication logs to `log.json`

- **Alerting System**
  - Base `Alert` class with derived `EmailAlert` and `SMSAlert`
  - `AlertManager` for JSON-based persistence
  - `CentralNotifier` singleton for centralized notifications
  - Utility functions and templates for alert display and pairing

---

## Project Structure

> Files are now organized into `src/` (implementations) and `include/` (headers & third‑party libs) with clear module boundaries.

- **Root**
  - `makefile` — builds the unified command-center app into `r.out`.
  - `README.md` — documentation.
  - `users.txt`, `messages.txt`, `log.txt`, `log.json` — runtime data files.

- **`include/`**
  - `User.h`, `Admin.h`, `Officer.h`, `Soldier.h`, `Message.h`
  - `Inventory.h`
  - `IDS.h`
  - `SecureCommunication.h`
  - `Alert.h`
  - `json.hpp`, `nlohmann/json.hpp` — nlohmann JSON library.

- **`src/app/`**
  - `main.cpp` — main entrypoint:
    - Shows the **Main Project Menu**.
    - Dispatches to:
      - `launchUserSystem`
      - `launchIDSSystem`
      - `launchInventorySystem`
      - `launchSecureCommunicationSystem`
      - `launchAlertSystem`

- **`src/core/`** (user domain + messaging)
  - `User.cpp` — base `User` logic and `authenticateUser` helper.
  - `Admin.cpp`, `Officer.cpp`, `Soldier.cpp` — role dashboards and reports.
  - `Message.cpp` — persistent user messaging.

- **`src/modules/ids/`**
  - `sensors.cpp` — `Sensors`, `MotionSensor`, `HeatSensor`, `SensorInventory`.
  - `intrusion.cpp` — `Intruder`, `IntrusionLog`, `Logger`, `ThreatLevel`.

- **`src/modules/inventory/`**
  - `Inventory.cpp` — `Equipment`, `MaintenanceRecord`, `Inventory` singleton.

- **`src/modules/secure_comm/`**
  - `SecureCommunication.cpp` — `Encryption`, `CaesarEncryption`, `UserManagement`, `SecureMessage`, `LogManager`.

- **`src/modules/alerts/`**
  - `Alert.cpp` — `Alert` base, `EmailAlert`, `SMSAlert`, `AlertManager`, `CentralNotifier`.

- **`src/demos/`**
  - `Usermain.cpp`, `InventoryMain.cpp`, `SecureCommunicationMain.cpp`, `AlertMain.cpp` — standalone demo entrypoints for individual modules.

- **Other runtime JSON/text assets**
  - `alerts.json` — alert definitions and persisted alerts.
  - `inventory.json` (optional) — example inventory snapshot if you save using that filename.

---

## Data Files & Formats

- **`users.txt`**
  - Format: `username password role`
  - Example:

    ```text
    admin1 admin123 Admin
    officer1 off123 Officer
    soldier1 sol123 Soldier
    ```

- **`issues.txt`**
  - Used by `Soldier` and `Officer` for issue reporting/approval.
  - Each line contains the issue data (ID, title, description, status).  
    The code reads and updates these entries to manage status transitions.

- **`messages.txt`**
  - CSV-style: `sender,receiver,content`
  - Used by `Message` to store and retrieve messages.

- **`log.json`**
  - JSON object of log entries for **Secure Communication** (via `LogManager`).

- **`log.txt`**
  - Plain-text logs for IDS `Logger` (intrusion-related events).

- **`alerts.json`**
  - Array of alert objects with fields `type`, `id`, `message`, `level`, `timestamp`.

---

## Building & Running

### Requirements

- C++11-compatible compiler (e.g., `g++`)
- A Windows environment is assumed for some features (e.g., `Beep` from `windows.h`).

### Using the Provided Makefile (Recommended)

From the project root:

```bash
make run
```

This will:

- Compile all sources under `src/` with headers from `include/` into `r.out`.
- Run the resulting executable.

To just build without running:

```bash
make compRun
```

To clean compiled binaries:

```bash
make clean
```

### Manual Compilation (Example)

If you prefer not to use `make`, follow the `SRCS` list in `makefile` and compile with `-Iinclude`, for example:

```bash
g++ -std=c++11 -Iinclude src/app/main.cpp src/core/User.cpp src/core/Admin.cpp src/core/Officer.cpp src/core/Soldier.cpp src/core/Message.cpp src/modules/ids/sensors.cpp src/modules/ids/intrusion.cpp src/modules/inventory/Inventory.cpp src/modules/secure_comm/SecureCommunication.cpp src/modules/alerts/Alert.cpp -o MilitaryManagementSystem
```

Then run:

```bash
./MilitaryManagementSystem
```

---

## Application Flow

1. **Start the application**  
   - Main menu appears: choose between User System, IDS, Inventory, Secure Communication, Alert System, or Exit.

2. **User System**
   - Enter **username** and **password**.
   - Credentials are validated against `users.txt` using `authenticateUser`.
   - Depending on the stored role, the system launches:
     - `Admin::performTask`
     - `Officer::performTask`
     - `Soldier::performTask`
   - Within each dashboard:
     - Access role-specific actions (account management, issue workflows, reports).
     - Optionally use the messaging center to send/view/edit messages.

3. **IDS**
   - Manage sensors, view all sensors, detect intrusions, analyze threat levels.
   - Generate reports and export/import JSON files of intrusion logs.

4. **Inventory**
   - Add/remove equipment and (optionally) attach maintenance records.
   - Persist and reload inventory from JSON.
   - Validate that equipment IDs exist and display summaries.

5. **Secure Communication**
   - Authenticate within the secure-comm module.
   - Encrypt and decrypt messages via Caesar cipher.
   - Retry sending messages with basic error handling.
   - View and manage chronological logs in `log.json`.

6. **Alerts**
   - Load existing alerts from `alerts.json`.
   - Add new alerts and broadcast them through `CentralNotifier`.
   - Save updated alert sets back to JSON and visualize them via `AlertManager`.

---

## Coding & Design Notes

- **Architecture**
  - Modular design with each subsystem encapsulated in its own header/implementation pair.
  - Use of **inheritance**, **polymorphism**, **friend classes**, **operator overloading**, **templates**, and **singletons** to demonstrate modern C++ concepts in a realistic domain.

- **Error Handling**
  - File operations are checked and provide clear error messages.
  - Inventory and secure-communication modules use exceptions where appropriate.

- **UI/UX (Console)**
  - Consistent, menu-driven navigation.
  - Clear, labeled sections for each subsystem.
  - Focus on a **command-center** feel within the constraints of a console UI (panels, headers, separators).

---
