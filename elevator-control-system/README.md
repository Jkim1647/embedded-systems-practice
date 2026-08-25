# Elevator Control System

ATmega128 기반 2대 엘리베이터 제어 시뮬레이션. 제54회 전국기능경기대회(2019, 장려상) 3과제 "Embedded system Programming"에서 작업한 임베디드 프로그래밍 결과물입니다.

## 과제 개요 (요약)

- **과제명**: Embedded system Programming · **제한시간**: 3시간
- 빌딩/아파트에서 흔히 쓰이는 2대(ELV-1, ELV-2) 엘리베이터 제어 시스템을 구현하는 과제입니다. 각 층의 UP/DOWN 스위치를 눌렀을 때 정해진 우선순위 규칙에 따라 두 엘리베이터 중 하나가 호출에 응답합니다.
- 도어가 닫히는 중 초음파 센서로 끼임을 감지하고, 온도 센서로 내부 온도가 기준치를 넘으면 비상 상태로 전환합니다.
- 각 층/엘리베이터 내부 스위치는 LED 내장형이며, 승강기 이동 상태는 각 층과 내부의 OLED로 표시합니다.
- 관리실용 별도 제어부("Sub Control PCB")를 두어 메인 MCU와 통신하며, 이동 상황·탑승 여부·현재 위치/인원/내부온도 등을 관리실 LCD에 표시합니다.
- 주어진 예제 코드(GccApplication1 등)를 참조/수정하는 것이 허용된 과제이며, 이 저장소의 코드는 그 요구사항을 구현한 최종 결과물입니다.

## 포함된 파일

- `main.c` — 엘리베이터 이동/정지/도어 제어 로직, 타이머 인터럽트, UART 통신, 센서/부저/LED 표시 처리
- `UART1.c` / `UART1.h` — UART1 송수신 드라이버

당시 프로젝트 폴더에 포함되어 있던 서드파티 라이브러리(OLED 디스플레이 드라이버, Atmel 자동생성 I2C 라이브러리 등)는 저작권 문제로 제외했습니다.

---

# Elevator Control System

Dual-elevator control simulation on ATmega128. This is the embedded-programming submission for Task 3 ("Embedded System Programming") at the 54th National Skills Competition (2019, Merit Award).

## Task summary

- **Task**: Embedded System Programming · **Time limit**: 3 hours
- Implement a 2-elevator (ELV-1, ELV-2) control system, the kind used in buildings and apartments. Pressing an UP/DOWN switch on any floor dispatches whichever elevator wins a defined priority rule.
- An ultrasonic sensor detects door-pinch during closing, and a temperature sensor triggers an emergency state if cabin temperature exceeds a threshold.
- Floor and in-cabin switches have built-in LEDs; each floor and the cabin interior show elevator position on an OLED.
- A separate management-room control unit ("Sub Control PCB") communicates with the main MCU, displaying movement status, occupancy, position, passenger count, and cabin temperature.
- Referencing/modifying a given example codebase was permitted for this task; the code here is the finished implementation of the requirements.

## Contents

- `main.c` — elevator movement/stop/door control logic, timer interrupts, UART comms, sensor/buzzer/LED handling
- `UART1.c` / `UART1.h` — UART1 TX/RX driver

Third-party libraries that were in the original project folder (an OLED display driver, Atmel's auto-generated I2C library) are excluded for copyright reasons.
