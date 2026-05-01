# Turn Based Battle System
> Unreal Engine 5로 구현한 턴제 전투 시스템 포트폴리오

데모 영상

[![Video Label](http://img.youtube.com/vi/WryUAEmEzMU/0.jpg)](https://youtu.be/WryUAEmEzMU)
[![YouTube](https://img.shields.io/badge/YouTube-Demo-red?logo=youtube)](https://www.youtube.com/watch?v=WryUAEmEzMU)
---
## 프로젝트 개요

| 항목 | 내용 |
|------|------|
| **엔진** | Unreal Engine 5.5 |
| **언어** | C++, Blueprint |
| **개발 인원** | 1인 |
| **핵심 목표** | 게임 기능 구현을 넘어 유지보수 가능한 시스템 설계 |

사용 모듈
`Core` `CoreUObject` `Engine` `InputCore` `EnhancedInput` `UMG` `GameplayTags` `Slate` `SlateCore`

---
## 주요 구현 기능

### 1. 레이어 기반 UI 관리 시스템
- **GameInstanceSubsystem**을 활용한 중앙 집중형 UI 관리
- **Widget Switcher**로 레이어(Frontend / GameHud / GameMenu / Modal)를 분리하여 독립적인 위젯 업데이트 가능
- **GameplayTag**로 위젯을 식별 및 관리해 편의성 향상
- 코드를 작성할 수 없는 인원도 활용할 수 있도록 **블루프린트 노드** 노출

```
Request → UiSubsystem → Add Widget → Find Focus → Callback
```

### 2. 게임패드 및 키보드 입력 지원
- 입력 시 디바이스를 감지하고 UiSubsystem을 통해 전달
- 디바이스 전환 시 UI 이미지 자동 변경 (게임패드 ↔ 키보드)
- 매 로직마다 이미지를 탐색하는 비효율을 방지하기 위한 **이미지 캐싱** 적용

### 3. 데이터 테이블 기반 데이터 관리
- 스킬, 아이템, 캐릭터 등 모든 수치를 **DataTable**로 관리
- 데이터 변경 시 추가 빌드 없이 즉시 반영
- CSV 파일로 에디터 외부에서도 테스트 가능
- GameInstance를 활용해 전투마다 다른 설정(적 수, 아이템 구성 등) 사용 가능

### 4. 비동기 로딩 기반 최적화
- `TSoftObjectPtr`를 사용해 캐릭터 생성 시 필요한 데이터만 비동기 로딩
- 사용하지 않는 에셋은 메모리에 올리지 않아 메모리 사용 최적화

### 5. 속도 기반 턴제 전투 시스템
- 캐릭터의 Speed 스탯에 따라 다음 턴 시작 시간 계산
- 턴 시작 시간을 기준으로 정렬 후 순서 배분
- 컴포넌트 기반 전투 구조 (Cursor / Target / Attribute Handler)
- DataTable에서 어빌리티를 로드하여 캐릭터에 동적으로 부여

### 6. 기반 시스템 및 유틸리티
- **네비게이션바**: 표시할 키·텍스트·클릭 반응을 에디터에서 설정 가능한 컴포넌트
- **IMC 딜레이 해결**: 위젯 생성 시 IMC 등록 완료 전 키 이미지가 비어 보이는 문제를 Timer로 해결
- **템플릿 레이아웃**: 전체 UI에 일관된 레이아웃 적용
- **타겟팅 시스템**: 단일/전체 타겟 선택 지원

---
Contact

- **Email** : dltpgns97@gmail.com