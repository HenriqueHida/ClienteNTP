# Cliente NTP

## Ambiente de Desenvolvimento

. A aplicação foi desenvolvida utilizando:

-   **Linguagem de programação:** C
-   **Compilador:** GCC (GNU Compiler Collection)
-   **Terminal:** GNOME Terminal 3.44.0 do Linux Ubuntu
-   **Sistema Operacional:** Linux Ubuntu

## Construindo

1.  Certifique-se de que o GCC está instalado no sistema. Caso não esteja, instale com o seguinte comando:
    
    ```bash
    sudo apt update && sudo apt install gcc -y
    
    ```
3.  Compile o programa usando o GCC com o seguinte comando:
    
    ```bash
    gcc -o cliente_ntp cliente_ntp.c
    
    ```
    
    Esse comando irá gerar um executável chamado `cliente_ntp`.
    

## Executando

1.  Certifique-se de que o arquivo executável `cliente_ntp` foi gerado corretamente.
    
2.  Execute passando como argumento o endereço IP de um servidor NTP, como `time.google.com`
    
    ```bash
    ./cliente_ntp 216.239.35.0
    
    ```
    
    Substitua `216.239.35.0` pelo endereço IP do servidor NTP desejado.
    
3.  O programa irá exibir a hora atual obtida do servidor NTP.
    ```
    Data/hora: Thu Jan 09 17:19:54 2025
    
    ```
    

## Observações

-   Certifique-se de que o servidor NTP está acessível e que a rede não possui restrições que impeçam o envio/recebimento de pacotes UDP na porta 123.
