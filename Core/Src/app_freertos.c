/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "lvgl/lvgl.h"
#include "main_scr.h"
#include "jpeg_utils.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define video_h  480
#define video_w  800
#define NUM_SAMPLES 10
#define CLUSTER_SAMPLE 20
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern uint32_t *buf_direct_2;
extern uint32_t frame_buffer_size;
extern JPEG_HandleTypeDef hjpeg;
extern UART_HandleTypeDef huart1;
extern volatile uint32_t frame_counter;

// Render Time variables
extern volatile uint32_t current_ms;
extern volatile uint32_t last_vsync_ms;
extern volatile uint32_t render_time;

// Start-up Time variables
extern volatile uint32_t boot_start;
extern volatile uint32_t boot_stop;
extern volatile uint32_t boot_time;
extern volatile uint32_t boot_flag;

bool demo_complete = false;
UBaseType_t StackUsage;
float percentage = 0;
uint8_t cpu;
uint8_t fps;
uint32_t demo_frame_start = 0;
uint32_t demo_frame_end = 0;
uint32_t demo_total_frames = 0;
uint32_t demo_running = 0;       // 0 = off, 1 = running
uint32_t cluster_running = 0;
uint32_t sample_count = 0;
uint32_t fps_samples[CLUSTER_SAMPLE];
uint32_t render_time_samples[CLUSTER_SAMPLE];
uint32_t cpu_usage_samples[CLUSTER_SAMPLE];
uint32_t stack_usage_samples[CLUSTER_SAMPLE];
uint32_t heap_usage_samples[CLUSTER_SAMPLE];
uint32_t avg_fps = 0;
uint32_t avg_render_time = 0;
uint32_t avg_cpu_usage = 0;
uint32_t avg_stack_usage = 0;
uint32_t avg_heap_usage = 0;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 8192 * 4
};
/* Definitions for stat_print_task */
osThreadId_t stat_print_taskHandle;
const osThreadAttr_t stat_print_task_attributes = {
  .name = "stat_print_task",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 1024 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern void metrics_print(void);
extern TIM_HandleTypeDef htim2;
int GetTaskCPUUsage(osThreadId_t thread_id);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void stat_print_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 2 */
void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
	 __HAL_RCC_TIM2_CLK_ENABLE();

	    htim2.Instance = TIM2;
	    htim2.Init.Prescaler = 	40;		// 4 MHz tick
	    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	    htim2.Init.Period = 0xFFFFFFFF;  // Free running 32-bit counter
	    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	    HAL_TIM_Base_Init(&htim2);
	    HAL_TIM_Base_Start(&htim2);
}

__weak unsigned long getRunTimeCounterValue(void)
{
	return __HAL_TIM_GET_COUNTER(&htim2);
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of stat_print_task */
  stat_print_taskHandle = osThreadNew(stat_print_task, NULL, &stat_print_task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/

/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */

  /* Infinite loop */
  for(;;)
  {
	  lv_timer_handler();
	  osDelay(1);
  }
  /* USER CODE END defaultTask */
}

/* USER CODE BEGIN Header_stat_print_task */
/**
* @brief Function implementing the stat_print_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_stat_print_task */
void stat_print_task(void *argument)
{
  /* USER CODE BEGIN stat_print_task */
  /* Infinite loop */
  for(;;)
  {
	  metrics_print();
	  osDelay(1);
  }
  /* USER CODE END stat_print_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
int GetTaskCPUUsage(osThreadId_t thread_id)
{
    UBaseType_t taskCount;
    TaskStatus_t *pxTaskStatusArray;
    configRUN_TIME_COUNTER_TYPE totalRunTime;

    taskCount = uxTaskGetNumberOfTasks();
    pxTaskStatusArray = pvPortMalloc(taskCount * sizeof(TaskStatus_t));

    if (pxTaskStatusArray != NULL)
    {
        taskCount = uxTaskGetSystemState(pxTaskStatusArray, taskCount, &totalRunTime);

        if (totalRunTime > 0)
        {
            for (UBaseType_t i = 0; i < taskCount; i++)
            {
                if (pxTaskStatusArray[i].xHandle == (TaskHandle_t)thread_id)
                {
                    percentage = ((float)pxTaskStatusArray[i].ulRunTimeCounter / (float)totalRunTime) * 100.0f;
                    vPortFree(pxTaskStatusArray);
                    return (int)percentage;
                }
            }
        }
    }
}

void metrics_print(void)
{
    static uint32_t last_time = 0;
    static uint32_t last_frames = 0;

    uint32_t current_ms = HAL_GetTick();
    uint32_t elapsed_ms = current_ms - last_time;

    if (elapsed_ms >= 1000)
    {
        last_time = current_ms;
        StackUsage = (defaultTask_attributes.stack_size - (uxTaskGetStackHighWaterMark(defaultTaskHandle) * sizeof(StackType_t))); // In Bytes
        uint32_t heapUsed = (configTOTAL_HEAP_SIZE - xPortGetFreeHeapSize());
        uint32_t frames = frame_counter - last_frames;
        if (frames > 60) frames = 60;
        last_frames = frame_counter;

        fps = frames;
        cpu = GetTaskCPUUsage(defaultTaskHandle);

        if (demo_running) {
        	if (sample_count < NUM_SAMPLES) {
        		fps_samples[sample_count] = frames;
        		render_time_samples[sample_count] = render_time;
        		cpu_usage_samples[sample_count] = GetTaskCPUUsage(defaultTaskHandle);
        		stack_usage_samples[sample_count] = StackUsage;
        		heap_usage_samples[sample_count] = heapUsed;
        		sample_count++;
        	}
        	// After 10 samples, calculate averages and complete demo
        	if (sample_count >= NUM_SAMPLES) {
                 // Calculate averages
        		uint32_t sum_fps = 0, sum_render_time = 0, sum_cpu_usage = 0, sum_stack_usage = 0, sum_heap_usage = 0;
        		for (uint32_t i = 0; i < NUM_SAMPLES; i++) {
        			sum_fps += fps_samples[i];
        			sum_render_time += render_time_samples[i];
        			sum_cpu_usage += cpu_usage_samples[i];
        			sum_stack_usage += stack_usage_samples[i];
        			sum_heap_usage += heap_usage_samples[i];
        		}
        		avg_fps = sum_fps / NUM_SAMPLES;
        		avg_render_time = sum_render_time / NUM_SAMPLES;
        		avg_cpu_usage = sum_cpu_usage / NUM_SAMPLES;
        		avg_stack_usage = sum_stack_usage / NUM_SAMPLES;
        		avg_heap_usage = sum_heap_usage / NUM_SAMPLES;

        		demo_running = false;
        		demo_complete = true;
        		sample_count = 0;
        	}
        }
        if (cluster_running) {
        	if (sample_count < CLUSTER_SAMPLE) {
        		fps_samples[sample_count] = frames;
        		render_time_samples[sample_count] = render_time;
        		cpu_usage_samples[sample_count] = GetTaskCPUUsage(defaultTaskHandle);
        		stack_usage_samples[sample_count] = StackUsage;
        		heap_usage_samples[sample_count] = heapUsed;
        		sample_count++;
        	}
        	// After 10 samples, calculate averages and complete demo
        	if (sample_count >= CLUSTER_SAMPLE) {
                 // Calculate averages
        		uint32_t sum_fps = 0, sum_render_time = 0, sum_cpu_usage = 0, sum_stack_usage = 0, sum_heap_usage = 0;
        		for (uint32_t i = 0; i < CLUSTER_SAMPLE; i++) {
        			sum_fps += fps_samples[i];
        			sum_render_time += render_time_samples[i];
        			sum_cpu_usage += cpu_usage_samples[i];
        			sum_stack_usage += stack_usage_samples[i];
        			sum_heap_usage += heap_usage_samples[i];
        		}
        		avg_fps = sum_fps / CLUSTER_SAMPLE;
        		avg_render_time = sum_render_time / CLUSTER_SAMPLE;
        		avg_cpu_usage = sum_cpu_usage / CLUSTER_SAMPLE;
        		avg_stack_usage = sum_stack_usage / CLUSTER_SAMPLE;
        		avg_heap_usage = sum_heap_usage / CLUSTER_SAMPLE;

        		cluster_running = false;
        		demo_complete = true;
        		sample_count = 0;
        	}
        }
    }
}
/* USER CODE END Application */
