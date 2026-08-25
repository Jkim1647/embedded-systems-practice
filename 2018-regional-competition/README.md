# 2018년도 서울시 지방기능경기대회 — 공업전자기기 (우수상)

2018년 서울시 지방기능경기대회 공업전자기기 직종에 응시해 5개 과제를 모두 수행했습니다. 이 해는 원본 설계/코드 파일이 남아있지 않아 이 저장소에 실제 파일은 없지만, 각 과제에서 무엇을 요구받았고 어떻게 수행했는지는 공식 문제 문서를 바탕으로 정리했습니다. (문제 원문은 저작권이 있는 공식 자료라 그대로 싣지 않고 제 말로 요약했습니다.)

## 1과제 — 인쇄회로기판 설계 및 기구물설계 (3시간)

주어진 회로도를 보고 인쇄회로기판(PCB)의 부품 배치·배선을 대회장에서 처음부터 직접 CAD로 설계하고, 이와 함께 케이스/패널 등 기구물 도면도 CAD로 작성하는 과제입니다. 직접 설계해 제출했으나, 이 아카이브에는 해당 결과 파일이 남아있지 않습니다.

## 2과제 — 하드웨어 설계 (신호등) (3시간)

신호등의 동작 상태를 모델링한 회로를 만능기판(prototype board)에 직접 납땜·배선하는 과제입니다. 저항 색띠 방향, 점퍼선 길이 제한(40mm 이내, 동박면 점퍼 금지) 등 세부 조립 규정을 지켜야 하며, LED 10개로 신호등 상태를 표시하고 Reset 스위치로 초기화합니다. 회로설계 답안지 작성 후 직접 제작까지 진행했습니다. PCB 자체가 없는(만능기판 수작업) 과제라 설계 파일은 존재하지 않습니다.

## 3과제 — 고장수리 및 측정 ("IC체커기") (지급 완제 기판)

대회 운영측이 미리 제작한 완제 기판(FRONT+MAIN 2장)에 고의로 심어둔 배선/부품 결함을 찾아 수리하고, 오실로스코프로 정상 동작을 측정해 제출하는 과제입니다. 기판 자체는 조직위 제작물이라 설계 파일은 없지만, 실제 결함 진단·납땜 수리·측정 작업은 직접 수행했습니다.

## 4과제 — 프로그램설계 (냉장고 시스템) (3시간)

지급된 ATmega128 완제 모듈+PCB에 C/ASM으로 가정용 냉장고 제어 프로그램을 작성하는 과제입니다. 세부 요구사항은 다음과 같았습니다.

- 온도 설정과 FND를 이용한 현재 온도 표시, LCD CGRAM을 이용한 "℃" 특수문자 표시
- 주변 밝기(CDS 센서)에 따른 램프 밝기 자동 조절
- 동작 상태(일반/파워 냉장 모드, 문 열림/닫힘)에 따른 LCD·LED 표시
- 스위치 입력으로 온도·조도 설정, 냉장고 문 개폐 시뮬레이션(문 열림 시간에 따른 온도 변화, 부저 경고)
- 앱 인벤터로 작성한 스마트폰 앱과 블루투스(HC-06)로 통신해 상태 확인·모드 제어
- 시리얼 통신(하이퍼터미널)으로 온도·조도 상태 실시간 출력

기판은 조직위가 제작한 완제 모듈이고, 이 아카이브에 남아있는 소스는 배포용 예제뿐이라 제 최종 코드는 없지만, 위 요구사항을 구현하는 작업을 직접 수행했습니다.

## 5과제 — 어셈블리 (3시간)

1~4과제에서 만든 Main PCB와 Front PCB를 볼트·너트·PCB Support·IDC/Flat Cable로 최종 결합하는 조립 과제입니다. 설계 파일이 아닌 기구 조립 작업이라 별도 결과물은 없습니다.

---

# 2018 Seoul Regional Skills Competition — Industrial Electronics (Excellence Award)

I competed in all 5 tasks of the 2018 Seoul Regional round. No original design/code files survive from this year, so there are no files here, but each task is documented below based on the official problem descriptions (paraphrased, not reproduced verbatim, since the originals are copyrighted).

## Task 1 — PCB Layout & Mechanical Design (3 hours)

Design the PCB layout from a given schematic, live at the venue, plus a mechanical enclosure/panel drawing in CAD. I completed and submitted this, but the result files don't survive in this archive.

## Task 2 — Hardware Design (traffic light) (3 hours)

Hand-solder and wire a circuit modeling traffic-light behavior onto prototype board, following detailed assembly rules (resistor color-band orientation, jumper wires under 40mm, no jumpers on the copper side). 10 LEDs indicate signal states; a reset switch re-initializes. No PCB design file exists for this task since it's hand-wired.

## Task 3 — Fault-Finding & Measurement ("IC checker") (organizer-fabricated board)

Diagnose and repair deliberately-planted wiring/component faults on a pre-fabricated board (FRONT+MAIN, supplied by the organizers), then verify correct operation with an oscilloscope. The board itself isn't my design, but the fault diagnosis, repair soldering, and measurement work was mine.

## Task 4 — Program Design (refrigerator system) (3 hours)

Write a C/ASM control program for a home-refrigerator simulation on a supplied ATmega128 module+PCB:

- Temperature setpoint and current-temp display on 7-segment, with a custom "°C" character via LCD CGRAM
- Automatic lamp brightness adjustment from an ambient-light (CDS) sensor
- LCD/LED display driven by mode (normal/power-cooling) and door state
- Switch-driven temperature/brightness setting, door-open simulation (temp drift over time, buzzer warnings)
- Bluetooth (HC-06) link to an App Inventor smartphone app for status/mode control
- Serial output (HyperTerminal) of live temperature/brightness

The board is an organizer-fabricated module, and only the distributed example source survives in this archive — but implementing the above was my own work.

## Task 5 — Assembly (3 hours)

Mechanically combine the Main and Front PCBs from the earlier tasks using bolts, nuts, PCB standoffs, and IDC/flat cable. A hands-on assembly task with no design file to show.
