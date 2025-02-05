# Temporizador de um Disparo (One Shot) com Raspberry Pi Pico W

## Descrição do Projeto

Este projeto implementa um **sistema de temporização para acionamento de LEDs** utilizando um **botão (pushbutton)**. O sistema é desenvolvido para o microcontrolador **Raspberry Pi Pico W** e utiliza a função `add_alarm_in_ms()` do Pico SDK para controlar os estados dos LEDs.

---

## Materiais Necessários

- **Raspberry Pi Pico W**
- **3 LEDs** (azul, vermelho e verde)
- **3 Resistores de 330 Ω** (para limitar a corrente dos LEDs)
- **1 Botão (Pushbutton)**
- **Bitdoglab** e **protoboard** para conexões
- **Software Pico SDK** (configurado no ambiente de desenvolvimento)
- **Compilador GCC para ARM** (já incluído no Pico SDK)
- **Ferramenta cmake** para compilação

---

## Instruções de Uso de Conexões de Hardware

Conecte os componentes ao Raspberry Pi Pico W em um simulador Wokwi conforme a tabela abaixo:

| Componente  | Pino GPIO no Pico W |
|-------------|---------------------|
| LED Azul    | GPIO 11             |
| LED Vermelho| GPIO 12             |
| LED Verde   | GPIO 13             |
| Botão       | GPIO 5              |

### Observações:

- O **botão** está conectado com um **resistor pull-up** interno (configurado no código).
- **Resistores de 330 Ω** estão conectados em série com os LEDs para limitar a corrente.

---

## Instruções de Funcionamento do Projeto

Este projeto implementa um **sistema de temporização para acionamento de LEDs** utilizando um **botão (pushbutton)** no **Raspberry Pi Pico W**. O sistema controla três LEDs (azul, vermelho e verde) com base em um temporizador de **3 segundos**.

### Como Funciona:

1. **Botão Pressionado:**
   - Quando o **botão é pressionado**, os **três LEDs** ficam ligados (todos em nível alto).
   - Após **3 segundos**, **dois LEDs** permanecem ligados (**vermelho e verde**).
   - Após mais **3 segundos**, **apenas um LED** permanece ligado (**verde**).
   - Após mais **3 segundos**, **todos os LEDs** são desligados.

2. **Restrição do Botão:**
   - O **botão só pode iniciar uma nova sequência** quando todos os LEDs estiverem desligados.
   - Durante a execução da sequência (LEDs acesos), o botão **não tem efeito**.

---

## Temporizador:

- O **temporizador** é ajustado para um atraso de **3 segundos (3000 ms)** entre cada mudança de estado dos LEDs.
- A mudança de estado dos LEDs é renovada em uma função de retorno de chamada chamada `turn_off_callback()`.

---

## Simulação no Wokwi

- O projeto já está implementado e pronto para ser **compilado e rodado no simulador Wokwi**. Não é necessário fazer configurações adicionais para testar.

---

## Estrutura do Código

O código-fonte completo está disponível no repositório. Ele inclui funções para:

- Configurar os pinos **GPIO**.
- Configurar um **botão (pushbutton)**.
- Acionar os **LEDs** de acordo com o estado de temporização.
  
---

## Melhorias Futuras

- **Implementar um debounce mais robusto** para o botão.
- **Adicionar suporte a eventos rápidos** para respostas mais rápidas ao botão.
- **Permitir configurações sem tempo de atraso** entre os estados dos LEDs.

---

## Licença

Este programa foi desenvolvido como um **exemplo educacional** e pode ser usado gratuitamente para **fins de estudo e aprendizagem**.

---

## Autora

**RAYANE QUEIROZ DOS SANTOS PASSOS**
