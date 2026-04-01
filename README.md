# STM32U5G9J-DK2 LVGL Benchmark Project

This project is used to generate **benchmark results (Matrices)** on the **STM32U5G9J-DK2** board using **LVGL**.

---

## 1. Required Software

Install the following software before building the project:

- **STM32CubeIDE**
- **Operating System:** Linux

You can download STM32CubeIDE from the STMicroelectronics website.

---

## 2. Clone the Repository

Clone the repository using the following command:

```bash
$ git clone https://github.com/Silicon-Signals/stm32u5g9j-dk2-lvgl-benchmark.git
```
Or download the ZIP file

---

## 3. SetUp and Run the Project

- **Open the Project in STM32CubeIDE**

  - Open **STM32CubeIDE**, then import the project:
  - Go to **File → Open Projects from File System**.
  - Select **Directory**.
  - Browse and choose the **cloned project folder**.
  - Click **Finish** to import the project into STM32CubeIDE.

- **Build the Project**

  - Click the **Build (🔨 hammer)** icon in STM32CubeIDE to build the project.
  - Use the **Debug configuration**, which already includes the required optimization settings.

- **Flash the Project to the Board**

  - Click the **Run (▶ play)** icon to upload the project to the board.
  - After flashing is complete, the **benchmark UI will appear on the board display**.

