# PILOSOPHERS
deadlock 문제의 대표적인 예시로 거론되는 철학자 식사 문제를 멀티 쓰레딩으로 구현한 프로그램

## 사용법
```
./philo <args1> <args2> <args3> <args4> (<args5>)
```
- **args1 : number_of_philosophers**
  - 전체 철학자의 수이자 포크의 개수

- **args2 : time_to_die (milliseconds)**
  - 철학자가 마지막으로 밥을 먹기 시작한 시간 이후로 밥을 먹지 못했을때 죽는 시간 

- **args3 : time_to_eat (milliseconds)**
  - 철학자가 밥을 먹는데 걸리는 시간

- **args4 : time_to_sleep (milliseconds)**
  - 철학자가 자는데 걸리는 시간
  
- **args5 : number_of_times_each_philosopher_must_eat (optional argument)**
  - 철학자가 채워야하는 식사 횟수
  - 모든 철학자가 이 횟수를 채우면 시뮬레이션 종료
  - 선택적 argument로 입력하지 않을 시 철학자가 죽을때까지 시뮬레이션 실행

## 프로그램 설명

### 철학자의 행동 패턴

- 철학자는 다음 행동 패턴을 반복한다.
  - **take a fork (왼손, 오른손 1번씩)**
    - 가능한 경우 포크를 집는다.
    - 옆사람이 포크를 사용중이면 기다린다. (비선점)
    - 기다리는 동안 반대손에 잡은 포크는 내려놓지 않는다. (점유 대기)

  - **eat**
    - 정해진 시간동안 밥을 먹는다.
    - 밥을 다 먹을때까지 포크를 내려놓지 않는다. (상호 배제)
    - 밥을 다 먹으면 왼손, 오른손 포크를 다 내려 놓는다.

  - **sleep**
    - 밥을 다 먹고 포크를 내려놓으면 정해진 시간만큼 잔다.

  - **think**
    - 자고 일어나면 생각을 한다.
    - 포크를 집을 수 있으면 바로 집는다.
    - 딱히 특별한 행동이 아닌 아무것도 안 하는 상태라 보면 된다.
   
- 철학자가 죽으면 프로그램을 종료한다.
  - **die**
    - 마지막으로 밥을 먹은 시간 후로 정해진 시간이 지나면 철학자가 죽는다.
    - 한 명이라도 철학자가 죽으면 프로그램을 종료한다.

## 프로그램 특징

### 멀티 쓰레딩 프로그램
- 철학자는 전부 쓰레드로 만들어진다.
- 메인 쓰레드에서 철학자 쓰레드를 모니터링한다.
- 메인 쓰레드에서 pthread_join()으로 철학자 쓰레드들의 종료를 기다린다.

### 뮤텍스를 이용한 data race 방지
- 포크와 같은 자원들은 쓰레드끼리 공유하므로 mutex를 이용해 동기화한다.

### 데드락 방지
- 어떤 상황에서든 데드락이 발생하지 않도록 만든다.
  - 모든 철학자가 같은 손에 포크를 1개씩 들어 그 누구도 못 먹는 상황.
- 데드락의 4조건 중 원형 대기를 없애서 데드락을 피한다.
  - 짝수의 철학자는 왼쪽, 홀수의 철학자는 오른쪽의 포크를 먼저 잡는다.
  - 만약 잡으려는 포크가 사용중이면 반대쪽을 보지 않고 끝까지 기다린다.
  - 이로써 원형 대기가 없어져 절대 데드락이 일어나지 않는다.

## 프로그램 출력
### TimeStamp ms 에, N 번째 철학자가 특정 행동을 했을때의 출력 포맷
- **take a fork**
  ```
  TimeStamp N has taken a fork 
  ```
- **eat**
  ```
  TimeStamp N is eating
  ```
- **sleep**
  ```
  TimeStamp N is sleeping
  ```
- **think**
  ```
  TimeStamp N is thinking
  ```
- **die**
  ```
  TimeStamp N died
  ```

## build
```
make
```
- philo 프로그램 생성
```
make clean
```
- philo 생성시 만들어진 .o 파일들 삭제
```
make fclean
```
- make clean + philo 파일 삭제
```
make re
```
- make fclean + make


