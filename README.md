Temporizador de um disparo (One Shot) com Raspberry Pi Pico W
Este projeto implementa um sistema de temporização para acionamento de LEDs utilizando um botão (pushbutton). O sistema é desenvolvido para o microcontrolador Raspberry Pi Pico W e utiliza a função add_alarm_in_ms() do Pico SDK para controlar os estados dos LEDs

Materiais necessários
Raspberry Pi Pico W

3 LEDs (azul, vermelho e verde)

3 Resistores de 330 Ω (para limitar a corrente dos LEDs)

1 Botão (Pushbutton)

Jumpers e protoboard para conexões

Software
Pico SDK (configurado no ambiente de desenvolvimento)

Compilador GCC para ARM (já incluído no Pico SDK)

Ferramenta cmake para compilação


Instruções de Uso
Conexões do Hardware

Conecte os componentes ao Raspberry Pi Pico W no simulador do wokwi conforme a tabela abaixo:

Componente	Pino GPIO no Pico W
LED Azul	GPIO 11
LED Vermelho	GPIO 12
LED Verde	GPIO 13
Botão	GPIO 5
Resistores	Conectados em série com os LEDs
Certifique-se de que:

O botão está conectado com um resistor pull-up interno (configurado no código).

Os resistores de 330 Ω estão conectados em série com os LEDs para limitar a corrente.

Instruções de Funcionamento do Projeto

Este projeto implementa um sistema de temporização para acionamento de LEDs utilizando um botão (pushbutton) no Raspberry Pi Pico W. O sistema controla três LEDs (azul, vermelho e verde) com base em um temporizador de 3 segundos.

Como Funciona
Botão Pressionado:

Quando o botão é pressionado, os três LEDs são ligados (todos em nível alto).

Após 3 segundos, dois LEDs permanecem ligados (vermelho e verde).

Após mais 3 segundos, apenas um LED permanece ligado (verde).

Após mais 3 segundos, todos os LEDs são desligados.

Restrição do Botão:

O botão só pode iniciar uma nova sequência quando todos os LEDs estiverem desligados.

Durante a execução da sequência (LEDs ligados), o botão não tem efeito.

Temporizador:

O temporizador é ajustado para um atraso de 3 segundos (3000 ms) entre cada mudança de estado dos LEDs.

A mudança de estado é implementada em uma função de callback chamada turn_off_callback().

Simulação no Wokwi

Já está implementado no projeto é só compilar e rodar no simulador.

Estrutura do Código

O código fonte completo está disponível no repositório. Ele inclui funções para configurar os pinos GPIO, e um botão (pushbutton) , para acionar os LEDs correspondentes e gerar uma ordem para acionamento.

Melhorias Futuras
Implementar um debounce mais robusto para o botão.

Adicionar suporte a interrupções para uma resposta mais rápida ao botão.

Permitir ajustes no tempo de atraso entre os estados dos LEDs.

Licença
Este programa foi desenvolvido como um exemplo educacional e pode ser usado gratuitamente para fins de estudo e aprendizagem.

Autora:
RAYANE QUEIROZ DOS SANTOS PASSOS



