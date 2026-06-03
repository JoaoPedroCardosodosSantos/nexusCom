# NexusCom

Sistema de comunicação digital baseado em LoRa, desenvolvido inicialmente para Arduino e projetado para futura migração para ESP32.

O objetivo do projeto é fornecer uma plataforma de comunicação robusta, modular e expansível para ambientes sem infraestrutura de rede tradicional, utilizando uma interface gráfica própria, teclado matricial T9 e arquitetura baseada em eventos.

---

## Objetivos

* Comunicação ponto a ponto via LoRa
* Interface gráfica embarcada
* Entrada de texto estilo T9
* Gerenciamento de contatos
* Arquitetura orientada a eventos
* Preparação para migração para ESP32
* Futuro suporte a armazenamento persistente
* Futuro suporte a rede Mesh

---

## Status Atual

### Implementado

* Interface gráfica básica
* Sistema de telas
* Menu principal
* Tela de mensagens
* Seleção de contatos
* Teclado matricial 4x4
* Driver PCF8574
* Sistema T9
* Editor de texto
* Estado global do sistema
* Dispatcher de eventos
* Fila circular genérica
* Simulação de transmissão e recepção

### Planejado

* Serviço LoRa real
* Protocolo de comunicação
* Persistência de dados
* Sistema de configurações
* Gerenciamento avançado de contatos
* Histórico de mensagens
* Rede Mesh
* Migração para ESP32
* Criptografia ponta a ponta

---

## Arquitetura

O sistema é dividido em módulos independentes:

### Core

Responsável pelo funcionamento interno da aplicação.

* Dispatcher de eventos
* Fila circular
* Gerenciamento do estado global

### Eventos

Define os eventos utilizados pelo sistema.

Exemplos:

* EVENTO_TECLA
* EVENTO_TX
* EVENTO_RX
* EVENTO_CONTATO_TROCADO

### Teclado

Camada responsável pela entrada de dados.

Inclui:

* Driver PCF8574
* Leitura da matriz 4x4
* Debounce
* T9
* Editor de texto

### UI

Camada de interface gráfica.

Inclui:

* Telas
* Menus
* Área de mensagens
* Barra de status
* Editor de texto

### Model

Representação dos dados do sistema.

Exemplos:

* Contatos
* Mensagens
* Configurações

### LoRa

Camada de comunicação.

Responsável por:

* Envio
* Recepção
* Protocolo
* Controle da rede

---

## Estrutura do Repositório

```text
nexusCom/

├── firmware/
│   └── platformio/
│       ├── platformio.ini
│       └── src/
│
├── hardware/
│   ├── esquemas/
│   ├── pinagem/
│   ├── pcb/
│   └── componentes/
│
├── docs/
│   ├── arquitetura/
│   ├── protocolo/
│   ├── testes/
│   └── requisitos/
│
└── assets/
```

---

## Hardware Previsto

### Microcontroladores

* Arduino Uno (desenvolvimento inicial)
* ESP32 (versão futura)

### Comunicação

* SX1278
* SX1276
* Módulos compatíveis LoRa

### Interface

* Display ST7789
* Teclado matricial 4x4
* PCF8574

---

## Fluxo Geral

```text
Teclado
    ↓
Evento
    ↓
Dispatcher
    ↓
Processamento
    ↓
LoRa
    ↓
Contato Destino
```

---

## Compilação

### Requisitos

* PlatformIO
* VS Code ou PlatformIO Core
* Git

### Compilar

```bash
pio run
```

### Upload

```bash
pio run --target upload
```

### Monitor Serial

```bash
pio device monitor
```

---

## Roadmap

### Fase 1 — Base do Sistema

* [x] Interface gráfica
* [x] Teclado T9
* [x] Contatos
* [x] Estado global
* [x] Dispatcher
* [ ] Sistema de logs para monitoramento e diagnóstico do sistema

### Fase 2 — Comunicação

* [ ] Serviço LoRa
* [ ] Pacotes
* [ ] ACK
* [ ] Retransmissão

### Fase 3 — Persistência

* [ ] Armazenamento local
* [ ] Configurações
* [ ] Histórico

### Fase 4 — Rede

* [ ] Mesh
* [ ] Roteamento
* [ ] Descoberta de nós

### Fase 5 — Produção

* [ ] ESP32
* [ ] PCB dedicada
* [ ] Caixa impressa em 3D

---

##
