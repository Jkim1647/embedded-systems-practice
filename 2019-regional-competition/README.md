# 2019년도 서울시 지방기능경기대회 — 공업전자기기 (금상)

2019년 서울시 지방기능경기대회 공업전자기기 직종, 1과제(하드웨어설계)에서 설계·제출한 PCB입니다.

## 과제 개요 (요약)

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

---

# 2019 Seoul Regional Skills Competition — Industrial Electronics (Gold Award)

PCB submitted for Task 1 (Hardware Design) at the 2019 Seoul Regional round of the Industrial Electronics trade.

## Task summary

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
