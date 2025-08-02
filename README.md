# 🧘 Philosophers – 42 Lisbon

> A concurrent programming project simulating the famous **Dining Philosophers** problem using threads and mutexes. Developed as part of the 42 Lisbon core curriculum.

---

## 🧠 Project Overview

The **Philosophers** project explores the classic concurrency challenge of synchronizing multiple entities (philosophers) sharing finite resources (forks) without causing **deadlocks**, **race conditions**, or **starvation**.

Each philosopher alternates between three states:

1. **Thinking**
2. **Eating** (requires 2 forks)
3. **Sleeping**

The challenge lies in ensuring that no two neighboring philosophers eat at the same time using shared forks, while avoiding any philosopher from dying due to starvation.

---

## 📜 Rules

- Philosophers **don’t communicate** with each other.
- They must **not die** (i.e., fail to eat within a given time).
- **Two forks** are required to eat.
- Forks are shared between neighbors.
- The simulation must:
  - End when a philosopher dies.
  - Optionally end when all philosophers have eaten a certain number of times, if the limit is set.
- Output must be **synchronized** and time-stamped.

---

## ⚙️ Input Parameters

Your program must be run as:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

