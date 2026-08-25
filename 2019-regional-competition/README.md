# 2019년도 서울시 지방기능경기대회 — 공업전자기기 (금상)

2019년 서울시 지방기능경기대회 공업전자기기 직종에서 4개 과제를 모두 수행했습니다. 실제 설계 파일이 남아있는 건 1과제뿐이라 그것만 저장소에 올렸고, 나머지 과제는 무엇을 했는지 문서로 정리했습니다.

## 1과제 — 하드웨어설계 (PCB 설계, 3시간)

- **과제명**: 하드웨어설계 · **제한시간**: 3시간
- 주어진 재료로 두 가지 로직 회로를 설계하고 시뮬레이션으로 동작을 검증합니다.
  - Design A — 74LS90/74LS92 카운터 IC를 이용한 60분주 회로
  - Design B — 74LS00 NAND 게이트를 이용한 시퀀스 회로 (진리표 기반)
- 별도로 주어진 메인 회로(시간 반복 카운터 — 1초마다 업카운트되고, 설정한 값에 도달하면 0으로 초기화되어 지정한 횟수만큼 반복 동작)를 인쇄회로기판(PCB)으로 직접 배치·배선하여 Gerber/NC Drill 파일로 제출합니다.
- 완성된 보드는 최소한의 점퍼선으로 실장 조립까지 진행합니다.

(제한시간 내에 PCB 설계를 마치지 못한 선수를 위해 백업용 완제 기판이 지급되기도 하지만, 이 폴더의 결과물은 직접 설계를 완료해 제작·조립까지 진행한 것입니다.)

## 포함된 파일

`task1-hardware-design/pcb1/`
- `gerber/` — 원본 Gerber 파일 (Top/Bottom Copper, Silkscreen, Soldermask, Board Outline 등)
- `nc-drill/` — NC Drill 파일
- `render/` — 레이어별 렌더링 이미지 (아래 참고)

| 파일 | 내용 |
|---|---|
| `01-top-copper.png` | 상단 동박(배선) |
| `02-bottom-copper.png` | 하단 동박(배선) — 이 보드는 배선 대부분이 하단에 몰려 있습니다 |
| `03-top-silkscreen.png` | 상단 실크스크린 |
| `04-bottom-silkscreen.png` | 하단 실크스크린 |
| `05-top-soldermask.png` | 상단 솔더마스크 |
| `06-bottom-soldermask.png` | 하단 솔더마스크 |
| `07-board-outline.png` | 보드 외곽선 |

원본 CAD 프로젝트 파일(스키매틱)은 남아있지 않고 Gerber 제작 데이터만 보존되어 있습니다.

## 2과제 — 고장수리 및 측정 (조도 경보기, 2시간)

지급된 완제 PCB(운영측 제작)는 조도 경보기 회로입니다 — 버튼으로 경보 값을 설정하면(FND 3자리 표시), CDS 센서가 감지한 밝기가 설정값보다 커질 때 부저가 울립니다. 이 보드의 배선 5곳에 고의로 결함이 있어 이를 찾아 수리하고, 수리 전후 파형을 오실로스코프로 측정해 워드 답안지에 정리해 제출하는 과제입니다. IC는 소켓 없이 직접 PCB에 납땜해야 하는 등 세부 규정이 있습니다. 보드 자체는 조직위 제작물이라 설계 파일은 없지만, 결함 진단·수리·측정은 직접 수행했습니다.

## 3과제 — 프로그램설계 (계산기, 3시간)

숫자 입력, 지우기, 초기화와 사칙연산(+, −, ×, ÷, %) 및 소수점 계산이 가능한 계산기를 완성하는 과제입니다. 주어진 예제 프로그램을 참조하거나 수정해서 완성하도록 되어 있어, 이 아카이브에 남은 `Calculator.c`류 소스는 그 예제 프로그램이고 제가 직접 수정한 최종본은 별도로 보존되어 있지 않습니다. 지급된 완제 PCB에 조립·프로그래밍하는 과제라 설계 파일도 없습니다.

## 4과제 — 어셈블러 (조립, 3시간)

Main PCB, Display PCB, Front PCB를 IDC Cable로 연결하고 볼트·너트·PCB Support로 최종 결합하는 과제입니다. 만능기판은 배치도를 참고해 직접 가공해서 지참해야 했습니다. 기구 조립 작업이라 별도 설계 파일은 없습니다.

---

# 2019 Seoul Regional Skills Competition — Industrial Electronics (Gold Award)

I competed in all 4 tasks at the 2019 Seoul Regional round. Only Task 1's design files survive, so that's what's in the repo — the other tasks are documented below.

## Task 1 — Hardware Design (PCB layout, 3 hours)

- **Task**: Hardware Design · **Time limit**: 3 hours
- Design and simulate two small logic circuits from the given requirements:
  - Design A — a ÷60 counter built from 74LS90/74LS92
  - Design B — a sequence circuit built from 74LS00 NAND gates, driven by a given truth table
- Separately, lay out and route the PCB for the main circuit (a repeating interval counter — counts up once per second, resets to zero on reaching the target value, and repeats for a set number of cycles) and submit Gerber/NC Drill files.
- Assemble the finished board with as few jumper wires as possible.

(A fallback pre-fabricated board is available for anyone who doesn't finish the layout in time, but what's here is a completed, self-designed layout that was also assembled.)

## Contents

`task1-hardware-design/pcb1/`
- `gerber/` — raw Gerber files (top/bottom copper, silkscreen, soldermask, board outline, etc.)
- `nc-drill/` — NC drill file
- `render/` — per-layer rendered images (see table above)

Only the Gerber fabrication data survives from this session — the original CAD/schematic project file wasn't preserved.

## Task 2 — Fault-Finding & Measurement (light alarm, 2 hours)

The supplied pre-fabricated PCB (organizer-made) is a light-alarm circuit: buttons set a threshold (shown on a 3-digit display), and a buzzer sounds once a CDS light sensor reads brighter than that threshold. This board has 5 deliberately-planted wiring faults to find and repair, with before/after waveforms captured on an oscilloscope and written up in a submitted document. ICs must be soldered directly to the board (no sockets), among other rules. The board itself isn't my design, but the fault diagnosis, repair, and measurement were.

## Task 3 — Program Design (calculator, 3 hours)

Complete a calculator supporting digit entry, clear/reset, the four arithmetic operations plus modulo, and decimal calculation — by referencing or modifying a given example program. The `Calculator.c`-family source that survives in this archive is that given example; my own modified final version wasn't separately preserved. This task also runs on a supplied pre-fabricated PCB, so there's no design file either way.

## Task 4 — Assembler (Assembly, 3 hours)

Connect the Main, Display, and Front PCBs via IDC cable and bolt them together with PCB standoffs. The prototype board had to be hand-machined per a layout diagram and brought pre-cut. A hands-on assembly task with no design file to show.
