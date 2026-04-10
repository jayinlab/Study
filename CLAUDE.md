# Study Repository

## 목적

OpenCL driver 개발자를 목표로 한 학습 저장소.
C++ 알고리즘 공부와, GPU 컴퓨팅 스택(OpenCL → SPIR-V → Vulkan Compute → ANGLE-CL)을 코드로 이해하는 것이 목표.

## 디렉토리 구조

```
study/
├── cpp/                    # C++ 알고리즘 학습
│   ├── src/                # 소스 코드
│   ├── out/                # 컴파일 결과물 (바이너리)
│   └── input/              # 테스트 입력 데이터
│
└── driver/                 # OpenCL driver 개발 학습
    ├── opencl/             # OpenCL API, 런타임, 메모리 모델
    ├── spirv/              # SPIR-V IR (OpenCL C → SPIR-V → GPU)
    ├── vulkan-compute/     # Vulkan compute backend (graphics 제외)
    └── angle-cl/           # ANGLE의 OpenCL-on-Vulkan 구현 분석
```

## 학습 스택 (driver/ 의 레이어 순서)

```
OpenCL C 커널
    ↓  opencl/        OpenCL API, 런타임 동작, 메모리 모델, 커맨드 큐
    ↓  spirv/         SPIR-V 컴파일 결과물, clang/llvm-spirv, 명령어 구조
    ↓  vulkan-compute/ Vulkan compute pipeline, descriptor set, dispatch
    ↓  angle-cl/      위 레이어를 연결하는 OpenCL-on-Vulkan 구현체 분석
```

## 타겟 하드웨어

- AMD GPU (RDNA 아키텍처 중심)
- ROCm / HIP 생태계 참고

## 빌드 규칙 (cpp/)

- 소스: `cpp/src/*.cpp`
- 출력: `cpp/out/*.out`
- 컴파일 예시: `g++ -std=c++17 -o cpp/out/foo.out cpp/src/foo.cpp`

## 주의사항

- `driver/` 하위는 코드로 동작 원리를 이해하는 것이 목표 — 완성된 프로그램보다 실험적 스니펫 위주
- Vulkan은 compute 전용으로만 사용, graphics 파이프라인은 다루지 않음
