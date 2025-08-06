#!/bin/bash

LOG="minishell_test_log.txt"
> $LOG

function log_test {
    echo -e "\n=============================" >> $LOG
    echo -e "TESTE: $1" >> $LOG
    echo -e "=============================" >> $LOG

    # Cria input temporário com todos os comandos + exit
    printf "%s\nexit\n" "$2" > input.tmp
    ./minishell < input.tmp >> $LOG 2>&1
    rm input.tmp
}

# Mesmos testes de antes...
log_test "Comando simples - ls" "ls"
log_test "Comando simples - echo Hello World" "echo Hello World"
log_test "Comando com path absoluto" "/bin/echo Testando"
log_test "Built-in: cd .." "cd ..\npwd"
log_test "Built-in: export, echo e unset" "export TESTE=42\necho \$TESTE\nunset TESTE\necho \$TESTE"
log_test "Built-in: env" "env"
log_test "Built-in: exit" "exit"
log_test "Variável \$USER42" "export USER42=doglas\necho \$USER42"
log_test "Aspas simples bloqueando \$" "echo '\$USER42'"
log_test "Aspas duplas com \$" "echo \"Meu nome é \$USER42\""
log_test "Aspas simples" "echo 'texto simples'"
log_test "Aspas duplas com espaços e \$" "echo \"texto com \$USER42 e espaço\""
log_test "Nested quotes" "echo \"Um 'dentro' do outro\""
log_test "Saída >" "echo Hello > testfile.txt\ncat testfile.txt"
log_test "Saída >>" "echo Again >> testfile.txt\ncat testfile.txt"
log_test "Entrada <" "cat < testfile.txt"
log_test "Heredoc << EOF" "cat << EOF\nlinha 1\nlinha 2\nEOF"
log_test "Pipe simples" "ls | wc -l"
log_test "Pipe com grep" "echo -e \"a\\nb\\nc\" | grep b"
log_test "Código de saída após sucesso" "ls\necho \$?"
log_test "Código de saída após erro" "ls arquivo_inexistente\necho \$?"
log_test "Comando inexistente" "comando_invalido"
log_test "Redirecionamento inválido" "ls >"
log_test "Arquivo inexistente para leitura" "cat < nao_existe.txt"

echo -e "\n✅ Testes concluídos! Verifique o arquivo $LOG"
