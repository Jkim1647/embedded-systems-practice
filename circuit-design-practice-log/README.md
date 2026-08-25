# Circuit Design Practice Log (2019 전국기능경기대회 준비)

2019년 전국기능경기대회(공업전자기기 직종) 준비 과정에서 2019년 8월 15일부터 10월 4일까지
약 7주간 매일 진행한 OrCAD Capture 회로설계 / PCB 레이아웃 연습 기록입니다.

- 각 날짜별 폴더에 스키매틱(`.DSN`), 프로젝트 파일(`.opj`), PCB 레이아웃(`allegro/*.brd`)이 들어있습니다.
- 일부 폴더의 `재출`/`제출` 하위 폴더에는 당시 제출용으로 캡처한 PCB 배치도/배선도 이미지(PNG)가 포함되어 있습니다.
- `08-26-INCHEN-TEST.DSN` — 인천 국가대표 훈련장 방문 시기에 진행한 연습입니다.
- `last/LASTT.DSN` — 전국대회(2019.10.11) 직전 마지막 연습본입니다.

원본 파일은 OrCAD Capture/Allegro 포맷으로, 뷰어 없이는 미리보기가 되지 않습니다. `재출`/`제출` 폴더의 PNG 이미지로 PCB 배치/배선 결과를 확인할 수 있습니다.

## 제작용 레이어 렌더링 (01~08 PNG)

Gerber 데이터(`allegro/*.art`, RS-274X)가 남아있는 8개 세션(`3. capture3`, `7. capture4`, `10. capture6`, `12. capture8`, `24`, `25`, `34`, `last`)은 실제 PCB 제작에 필요한 레이어별 이미지를 직접 렌더링해 추가했습니다 (PyGerber 사용).

| 파일 | 내용 |
|---|---|
| `01-top-copper.png` | 상단 동박(배선) 레이어 |
| `02-bottom-copper.png` | 하단 동박(배선) 레이어 |
| `03-top-silkscreen.png` | 상단 실크스크린(부품 기호/레퍼런스) |
| `04-bottom-silkscreen.png` | 하단 실크스크린 |
| `05-top-soldermask.png` | 상단 솔더마스크(납땜 개구부) |
| `06-bottom-soldermask.png` | 하단 솔더마스크 |
| `07-board-outline.png` | 보드 외곽선 |
| `08-drill-drawing.png` | 드릴 도면(홀 사이즈/개수표) |

**`01-top-copper.png`가 없는 세션**(capture3/4/6/8)은 해당 시점에 상단 배선 작업이 아직 완료되지 않았던 것으로 보입니다 — 연습을 거듭하며 단면→양면 배선으로 발전해가는 과정을 보여줍니다.

일부 세션의 `재출`/`제출` 폴더에는 당시 실제 제출용으로 캡처한 PCB 이미지도 별도로 남아있습니다.
