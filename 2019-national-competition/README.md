# 제54회 전국기능경기대회 — 공업전자기기 (장려상)

2019년 제54회 전국기능경기대회 공업전자기기 직종, 1과제(하드웨어설계 — "납 연기 제거기")에서 설계·제출한 PCB입니다.

## 과제 개요 (요약)

- **과제명**: 하드웨어설계 (납 연기 제거기 구현) · **제한시간**: 5시간 30분 (회로설계 1시간 + PCB설계 2시간30분 + 조립·동작 2시간)
- **동작 요구사항**: 전원 스위치를 누르면 팬모터가 동작하고, 1~3단 스위치에 따라 팬 회전 속도(약풍/중풍/강풍)가 바뀝니다. 가변저항으로 LED 바그래프 점등 개수와 발진 주파수 등을 조절합니다.
- **회로설계(Design A/B/C)**: LM339 비교기 기반 LED 바그래프(Design A), 4071/4175 기반 시퀀스 회로(Design B), 4001 기반 약 430kHz 발진회로(Design C)를 설계하고 시뮬레이션으로 검증.
- **PCB 설계**: 검증된 메인 회로를 1-Layer(단면) PCB로 직접 배치·배선 — 부품은 TOP면, 배선은 BOTTOM면, 보드 크기 160×100mm, 비아/자동배선 금지, 배선 최소 폭 0.3mm 등 세부 규격을 지켜 설계. 완성 후 Gerber(Top/Bottom Layer, KeepOut/외곽선)와 NC Drill 파일을 제작용으로 제출.
- **조립**: 설계한 메인 보드와, 만능기판에 별도로 조립한 FRONT(패널) 보드를 결합해 실제 동작을 시연.

(제한시간 내 PCB 설계를 마치지 못한 선수를 위한 백업용 완제 기판이 지급되기도 하지만, 이 폴더의 결과물은 직접 설계를 완료해 제작·조립까지 진행한 것입니다.)

## 포함된 파일

`task1-lead-smoke-remover/pcb1/`
- `gerber/` — 원본 Gerber 파일 (프로젝트명 "lead smoke remover" 그대로 보존)
- `nc-drill/` — NC Drill 파일
- `render/` — 레이어별 렌더링 이미지

| 파일 | 내용 |
|---|---|
| `01-top-copper.png` | 상단 동박(배선) — 이 보드는 부품 패드 위주이고 실제 배선은 대부분 하단에 있습니다 |
| `02-bottom-copper.png` | 하단 동박(배선) |
| `03-top-silkscreen.png` | 상단 실크스크린 |
| `04-bottom-silkscreen.png` | 하단 실크스크린 |
| `05-top-soldermask.png` | 상단 솔더마스크 |
| `06-bottom-soldermask.png` | 하단 솔더마스크 |
| `07-board-outline.png` | 보드 외곽선 |

---

# 54th National Skills Competition — Industrial Electronics (Merit Award)

PCB submitted for Task 1 (Hardware Design — "lead smoke remover") at the 54th Korean National Skills Competition, Industrial Electronics trade.

## Task summary

- **Task**: Hardware Design, implementing a lead-smoke extractor fan unit · **Time limit**: 5h 30m (1h circuit design + 2h30m PCB design + 2h assembly/bring-up)
- **Behavior**: pressing the power switch starts the fan; a 3-position switch selects fan speed (low/medium/high); potentiometers adjust an LED bar-graph display and an oscillator frequency.
- **Circuit design (Design A/B/C)**: an LM339-comparator LED bar-graph (A), a 4071/4175-based sequence circuit (B), and a ~430kHz 4001-based oscillator (C) — each designed and verified by simulation.
- **PCB design**: laid out and routed the verified main circuit as a 1-layer PCB — components on top, routing on bottom, 160×100mm board, no vias or auto-routing, 0.3mm minimum trace width, and other spec constraints. Submitted Gerber (top/bottom layer, board outline) and NC Drill files for fabrication.
- **Assembly**: combined the designed main board with a separately hand-wired FRONT panel board (built on prototype board) to demonstrate the finished unit.

(A fallback pre-fabricated board is available for anyone who doesn't finish the layout in time, but what's here is a completed, self-designed layout that was also assembled.)

## Contents

`task1-lead-smoke-remover/pcb1/`
- `gerber/` — raw Gerber files (project name "lead smoke remover" preserved as-is)
- `nc-drill/` — NC drill file
- `render/` — per-layer rendered images (see table above)
