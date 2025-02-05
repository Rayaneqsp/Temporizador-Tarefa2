#include <stdio.h>          // Biblioteca padrão do C.
#include "pico/stdlib.h"    // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO e temporização.
#include "pico/time.h"      // Biblioteca para gerenciamento de temporizadores e alarmes.

// Definição dos pinos dos LEDs e do botão
#define LED_BLUE_PIN 11     // Pino GPIO 11 para o LED azul.
#define LED_RED_PIN 12      // Pino GPIO 12 para o LED vermelho.
#define LED_GREEN_PIN 13    // Pino GPIO 13 para o LED verde.
#define BUTTON_PIN 5        // Pino GPIO 5 para o botão.

// Estados dos LEDs
typedef enum {
    ALL_LEDS_ON,    // Todos os LEDs ligados.
    TWO_LEDS_ON,    // Dois LEDs ligados.
    ONE_LED_ON,     // Um LED ligado.
    ALL_LEDS_OFF    // Todos os LEDs desligados.
} LedState;

// Variáveis globais
volatile LedState currentState = ALL_LEDS_OFF;  // Estado atual dos LEDs.
volatile bool buttonPressed = false;            // Indica se o botão foi pressionado.
volatile bool timerActive = false;              // Indica se o temporizador está ativo.

// Função para configurar os pinos dos LEDs e do botão
void setup_pins() {
    gpio_init(LED_BLUE_PIN);
    gpio_init(LED_RED_PIN);
    gpio_init(LED_GREEN_PIN);
    gpio_init(BUTTON_PIN);

    gpio_set_dir(LED_BLUE_PIN, GPIO_OUT);
    gpio_set_dir(LED_RED_PIN, GPIO_OUT);
    gpio_set_dir(LED_GREEN_PIN, GPIO_OUT);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    gpio_pull_up(BUTTON_PIN);  // Habilita o resistor pull-up interno para o botão.
}

// Função para controlar os LEDs com base no estado atual
void update_leds() {
    switch (currentState) {
        case ALL_LEDS_ON:
            gpio_put(LED_BLUE_PIN, 1);
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_GREEN_PIN, 1);
            break;
        case TWO_LEDS_ON:
            gpio_put(LED_BLUE_PIN, 0);
            gpio_put(LED_RED_PIN, 1);
            gpio_put(LED_GREEN_PIN, 1);
            break;
        case ONE_LED_ON:
            gpio_put(LED_BLUE_PIN, 0);
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_GREEN_PIN, 1);
            break;
        case ALL_LEDS_OFF:
            gpio_put(LED_BLUE_PIN, 0);
            gpio_put(LED_RED_PIN, 0);
            gpio_put(LED_GREEN_PIN, 0);
            break;
    }
}

// Função de callback para gerenciar as transições de estado dos LEDs
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    switch (currentState) {
        case ALL_LEDS_ON:
            currentState = TWO_LEDS_ON;  
            break;
        case TWO_LEDS_ON:
            currentState = ONE_LED_ON;   
            break;
        case ONE_LED_ON:
            currentState = ALL_LEDS_OFF; 
            timerActive = false;         
            break;
        default:
            break;
    }

    update_leds();  // Atualiza o estado dos LEDs.

    // Se o estado atual não for ALL_LEDS_OFF, agenda o próximo callback
    if (currentState != ALL_LEDS_OFF) {
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }

    return 0;  // Retorna 0 para indicar que o alarme não deve se repetir automaticamente.
}

// Função principal
int main() {
    stdio_init_all();  // Inicializa a comunicação serial (para depuração, se necessário).
    setup_pins();      // Configura os pinos dos LEDs e do botão.

    while (true) {
        // Verifica se o botão foi pressionado e se o temporizador não está ativo
        if (gpio_get(BUTTON_PIN) == 0 && !buttonPressed && !timerActive) {
            buttonPressed = true;  // Marca o botão como pressionado.
            sleep_ms(50);          // Debounce simples (aguarda 50 ms para evitar leituras errôneas).

            // Verifica novamente o estado do botão após o debounce
            if (gpio_get(BUTTON_PIN) == 0) {
                currentState = ALL_LEDS_ON;  // Inicia a sequência com todos os LEDs ligados.
                timerActive = true;          // Ativa o temporizador.
                update_leds();               // Atualiza o estado dos LEDs.
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);  // Agenda o primeiro callback.
            }
        }

        // Verifica se o botão foi solto
        if (gpio_get(BUTTON_PIN) == 1) {
            buttonPressed = false;  
        }

        sleep_ms(10);  // Pequena pausa para reduzir o uso da CPU.
    }

    return 0;  
}
