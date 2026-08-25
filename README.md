# Embedded Systems Practice — 기능경기대회 준비 자료

서울로봇고등학교 공업전자기기 기능반 활동 및 전국기능경기대회 준비 과정에서 작성한 임베디드 C 코드, 회로/PCB 설계 자료입니다.

**대회 결과**
- 2018년 서울시 지방기능경기대회 — 우수상
- 2019년 서울시 지방기능경기대회 — 금상
- 2019년 전국기능경기대회(제54회) — 장려상

## 배경: 공업전자기기 종목이란

공업전자기기(Industrial Electronics)는 전국기능경기대회 직종 중 하나로, 산업 현장에서 쓰이는 전자 계측/제어 장비에 대한 이론과 회로 설계·PCB 설계·조립·고장수리 및 측정·임베디드 프로그래밍 능력을 겨루는 종목입니다. 매년 다른 문제가 출제되며, 지방대회에서 입상해야 전국대회에 진출할 수 있습니다.

경기는 보통 5개 내외의 세부 과제로 구성되고, 과제마다 성격이 다릅니다.

- **1과제(하드웨어설계/회로설계)** — 주어진 요구사항으로 로직 회로를 직접 설계·시뮬레이션하고, 그 회로를 바탕으로 인쇄회로기판(PCB) 레이아웃을 대회장에서 **직접, 처음부터** CAD로 설계해 Gerber/NC Drill 파일로 제출하는 과제입니다. (시간 내에 설계를 끝내지 못한 선수를 위한 백업용 완제 기판이 지급되기도 하지만, 정상적으로는 선수 본인이 설계합니다.)
- **2과제 이후(조립, 고장수리 및 측정, 프로그램 작성, 디스플레이 시스템 조립 등)** — 대부분 대회 운영측이 미리 제작한 기판(예: 회로에 고의로 결함을 심어둔 보드)을 지급받아 조립·수리·프로그래밍하는 과제입니다. 이 저장소에는 **1과제(PCB 설계)만** 포함했습니다 — 나머지 과제의 기판 설계 파일은 선수 개인이 만든 결과물이 아니라 대회 운영 자료이기 때문입니다.

## 프로젝트 구성

**PCB 설계 (대회 1과제 결과물)**
- [`2019-regional-competition`](./2019-regional-competition) — 2019년 서울시 지방기능경기대회 1과제 PCB 설계 (금상)
- [`2019-national-competition`](./2019-national-competition) — 제54회 전국기능경기대회 1과제 PCB 설계 "납 연기 제거기" (장려상)

**임베디드 C 코드**
- [`elevator-control-system`](./elevator-control-system) — ATmega128 기반 2대 엘리베이터 제어 시뮬레이션. UART 통신, 층 이동 로직, 센서/부저/LED 표시 구현
- [`motor-pwm-control`](./motor-pwm-control) — ATmega128 기반 PWM 모터 속도 제어 + 7세그먼트 디스플레이 (인터럽트 기반 실시간 제어)

**회로설계 연습**
- [`circuit-design-practice-log`](./circuit-design-practice-log) — 2019.08.15~10.04, 약 7주간 매일 진행한 OrCAD 회로설계/PCB 레이아웃 연습 기록 (39개 세션)
- [`circuit-design-problem-set`](./circuit-design-problem-set) — 회로설계(1과제) 연습 문제·정답 7종

모두 기능경기대회 준비 과정에서 작성한 실습/연습 자료이며, 상용 제품이 아닙니다. 대회 공식 문제지·정답지·채점기준표 등 저작권이 있는 원문 자료는 포함하지 않았고, 문제 내용은 이해를 돕기 위해 요약해 설명했습니다.

---

# Embedded Systems Practice — Korean National Skills Competition Prep

Embedded C code and circuit/PCB design work from my time on the Industrial Electronics skills team at Seoul Robot High School, preparing for South Korea's National Skills Competition (기능경기대회).

**Results**
- 2018 Seoul Regional Skills Competition — Excellence Award
- 2019 Seoul Regional Skills Competition — Gold Award
- 2019 National Skills Competition (54th) — Merit Award

## Background: the Industrial Electronics trade

Industrial Electronics is one of the trade categories in Korea's National Skills Competition, testing theoretical knowledge and hands-on skill in circuit design, PCB layout, assembly, fault-finding/measurement, and embedded programming for the kind of instrumentation and control equipment used in industry. The problem set is different every year, and competitors must place at the regional level to advance to nationals.

Each competition is broken into roughly five tasks, and they aren't all the same kind of work:

- **Task 1 (Hardware/Circuit Design)** — design a logic circuit from the given requirements, simulate it, then lay out the PCB for the main circuit **from scratch, live at the venue**, in CAD software, and submit Gerber/NC Drill files. (A backup pre-fabricated board is provided as a fallback for anyone who doesn't finish the layout in time, but the normal path is designing it yourself.)
- **Tasks 2 onward (assembly, fault-finding & measurement, programming, display system assembly, etc.)** — mostly involve working with a board the organizers already fabricated (e.g., one with faults deliberately built in) — assembling, repairing, or programming it. This repo includes **only Task 1 (PCB design)**; the board files for the other tasks aren't something I personally designed — they're competition infrastructure, not my own output.

## What's here

**PCB design (Task 1 submissions)**
- [`2019-regional-competition`](./2019-regional-competition) — 2019 Seoul Regional Competition, Task 1 PCB design (Gold Award)
- [`2019-national-competition`](./2019-national-competition) — 54th National Competition, Task 1 PCB design, "lead smoke remover" (Merit Award)

**Embedded C**
- [`elevator-control-system`](./elevator-control-system) — Dual-elevator control simulation on ATmega128: UART comms, floor-movement logic, sensor/buzzer/LED indicators
- [`motor-pwm-control`](./motor-pwm-control) — PWM motor speed control + 7-segment display on ATmega128, interrupt-driven

**Circuit design practice**
- [`circuit-design-practice-log`](./circuit-design-practice-log) — Daily OrCAD circuit/PCB layout practice, 2019-08-15 to 2019-10-04 (39 sessions)
- [`circuit-design-problem-set`](./circuit-design-problem-set) — 7 self-assembled circuit design practice problems with solutions

Everything here is practice/training material from competition prep, not a commercial product. Official copyrighted competition documents (problem sheets, answer keys, scoring rubrics) are not included — task descriptions are paraphrased for context.
