Here are the **first 100 function prototypes** from your `minishell` project, fully formatted and copy-paste ready for header files like `minishell.h`, `parser.h`, etc.:

---

### ✅ First 100 Function Prototypes

```c
int main(int argc, char **argv, char **envp); // Função principal do programa. Inicia o shell.
int shell_loop(t_shell *shell); // Loop principal do shell, onde os comandos são lidos e executados.
char *read_user_input(void); // Lê a entrada do usuário usando readline.
void display_prompt(void); // Mostra o prompt do shell na tela.
void free_user_input(char *line); // Libera a memória da linha lida do usuário.
int is_interactive_shell(void); // Verifica se o shell está rodando em modo interativo.
void init_readline(void); // Inicializa a configuração do readline.
void init_signals(void); // Configura os sinais para o modo do shell.
void reset_signals(void); // Restaura os sinais para o padrão.
void signal_handler_parent(int sig); // Manipulador de sinal no processo pai.
void signal_handler_child(int sig); // Manipulador de sinal no processo filho.
void enable_echoctl(void); // Ativa a exibição de caracteres de controle no terminal.
void disable_echoctl(void); // Desativa a exibição de caracteres de controle no terminal.
void set_signal_code(int code); // Define o código de saída com base em um sinal.
int get_signal_code(void); // Retorna o código de sinal armazenado.
t_token *tokenize_input(const char *line); // Tokeniza a linha de entrada em palavras-chave.
t_token *new_token(const char *value, int type); // Cria um novo token com valor e tipo.
void add_token(t_token **list, t_token *new); // Adiciona um novo token à lista de tokens.
void free_token_list(t_token *head); // Libera a lista de tokens.
int is_metachar(char c); // Verifica se o caractere é um metacaractere.
int is_operator(char c); // Verifica se o caractere é um operador de shell.
int is_quote(char c); // Verifica se o caractere é uma aspa.
int is_space(char c); // Verifica se o caractere é um espaço.
int is_end_of_token(char c); // Verifica se o caractere marca o fim de um token.
int token_type(char *str); // Determina o tipo de um token com base na string.
int is_word(const char *s); // Verifica se a string representa uma palavra válida.
void print_tokens_debug(t_token *tokens); // Mostra a lista de tokens para debug.
int contains_unclosed_quotes(const char *s); // Verifica se há aspas não fechadas na string.
int quotes_balanced(const char *line); // Verifica se as aspas estão balanceadas.
char *remove_quotes(const char *str); // Remove aspas de uma string.
int is_quoted_segment(const char *s, int i); // Verifica se o índice está dentro de aspas.
int quote_type(char c); // Retorna o tipo de aspa (simples ou dupla).
char *expand_variables(const char *line, t_env *env, int last_status); // Expande variáveis de ambiente e $?.
char *expand_var_token(const char *token, t_env *env); // Expande um token contendo variável.
char *expand_exit_status(const char *line, int status); // Substitui $? pelo status.
int is_expandable(char c); // Verifica se o caractere pode iniciar uma variável.
char *extract_var_key(const char *line, int *len); // Extrai a chave da variável de ambiente.
char *expand_env_value(const char *key, t_env *env); // Obtém o valor da variável do ambiente.
char *get_env_value(t_env *env, const char *key); // Retorna o valor de uma chave do env.
t_cmd *parse_tokens_to_cmds(t_token *tokens); // Constrói comandos a partir da lista de tokens.
t_cmd *new_command(void); // Cria uma nova estrutura de comando.
void add_command(t_cmd **cmds, t_cmd *new); // Adiciona comando à lista.
void free_command_list(t_cmd *cmds); // Libera todos os comandos da lista.
int count_command_segments(t_token *tokens); // Conta quantos comandos há em um pipeline.
int command_needs_pipe(t_token *tokens); // Verifica se há necessidade de pipe.
int command_is_empty(t_cmd *cmd); // Verifica se um comando está vazio.
int is_redirection_token(t_token *token); // Verifica se o token é um redirecionamento.
int handle_redirections(t_cmd *cmd); // Lida com os redirecionamentos de entrada/saída definidos no comando.
int setup_redir_input(t_redir *redir); // Configura a entrada de um comando com base no redirecionamento.
int open_input_file(const char *filename); // Abre um arquivo para leitura como entrada padrão.
int setup_redir_output(t_redir *redir); // Configura a saída de um comando com base no redirecionamento.
int open_output_file(const char *filename, int append); // Abre/cria um arquivo para escrita, com opção de append.
int setup_heredoc_pipe(char *delimiter, int *fd); // Prepara o pipe que será usado por um heredoc.
int read_heredoc_input(const char *delim, int fd[2]); // Lê a entrada até encontrar o delimitador do heredoc.
int create_heredoc(const char *delimiter); // Cria e configura um heredoc, pronto para ser lido.
void close_redirections(t_cmd *cmd); // Fecha todos os FDs abertos por redirecionamento de um comando.
void apply_redrections(t_cmd *cmd); // Aplica efetivamente os redirecionamentos no processo atual.
int handle_redir_error(const char *msg); // Exibe uma mensagem de erro relacionada a redirecionamento.
int is_pipe_token(t_token *token); // Verifica se o token representa um pipe ("|").
int execute_pipeline(t_cmd *cmds, t_shell *shell); // Executa múltiplos comandos conectados por pipe.
int execute_single_command(t_cmd *cmd, t_shell *shell); // Executa um comando isolado (sem pipe).
int spawn_child_process(t_cmd *cmd, t_shell *shell, int *fds, int is_last); // Cria um processo filho para o comando.
void child_process_exec(t_cmd *cmd, t_shell *shell, int is_last); // Executa o comando no processo filho.
char *resolve_command_path(char *cmd, t_env *env); // Resolve o caminho completo do executável com base no PATH.
int is_path_absolute_or_relative(const char *cmd); // Verifica se o comando é um path absoluto ou relativo.
int is_valid_executable(const char *path); // Verifica se o arquivo no path é executável.
int launch_execve(t_cmd *cmd, t_shell *shell); // Executa um comando externo usando `execve`.
void handle_exec_error(const char *msg); // Exibe mensagem de erro quando `execve` falha.
int setup_pipes(t_cmd *cmds, int ***pipes); // Cria e configura os pipes necessários para a pipeline.
void close_all_pipes(int **pipes, int count); // Fecha todos os FDs de pipes abertos.
void free_pipe_fds(int **pipes, int count); // Libera a memória alocada para os pipes.
int wait_for_all(t_cmd *cmds); // Aguarda todos os processos da pipeline finalizarem.
void update_exit_code_from_status(int status); // Atualiza o código de saída global a partir do status do filho.
int is_builtin(t_cmd *cmd); // Verifica se o comando é um builtin.
int execute_builtin(t_cmd *cmd, t_shell *shell); // Executa um comando builtin diretamente no processo pai.
int builtin_echo(t_cmd *cmd); // Implementação do comando `echo`, com suporte a `-n`.
int check_echo_flag(char *arg); // Verifica se o argumento de `echo` é a flag `-n`.
int builtin_cd(t_cmd *cmd, t_shell *shell); // Implementação do comando `cd`, com atualização de PWD e OLDPWD.
int update_pwd(t_shell *shell); // Atualiza a variável PWD após um `cd`.
int update_oldpwd(t_shell *shell); // Atualiza a variável OLDPWD após um `cd`.
int change_dir(const char *path, t_shell *shell); // Realiza a mudança de diretório e atualiza variáveis.
int builtin_pwd(void); // Mostra o diretório atual (implementação do `pwd`).
int builtin_env(t_cmd *cmd, t_env *env); // Mostra as variáveis de ambiente (como `env`).
int builtin_export(t_cmd *cmd, t_shell *shell); // Define variáveis de ambiente (`export`).
int validate_export_argument(const char *s); // Verifica se o argumento de `export` é válido.
int export_variable(const char *arg, t_shell *shell); // Adiciona ou modifica uma variável de ambiente.
void sort_and_print_env(t_env *env); // Mostra as variáveis exportadas em ordem alfabética.
int builtin_unset(t_cmd *cmd, t_shell *shell); // Remove uma variável de ambiente (`unset`).
int builtin_exit(t_cmd *cmd, t_shell *shell); // Encerra o shell (`exit`), com código de saída opcional.
int is_valid_exit_code_arg(const char *arg); // Verifica se o argumento passado para `exit` é um código válido.
int count_args(t_cmd *cmd); // Conta o número de argumentos de um comando.
void export_print_sorted(t_env *env); // Imprime as variáveis exportadas em ordem alfabética, com formato especial.
int env_key_exists(t_env *env, const char *key); // Verifica se uma chave de variável de ambiente já existe.
t_env *init_env_from_environ(char **envp); // Constrói a lista de variáveis de ambiente a partir do `envp`.
char **env_to_str_array(t_env *env); // Converte a lista ligada de variáveis em um array de strings (`char **`).
int set_env_value(t_env **env, const char *key, const char *value); // Define ou atualiza uma variável no ambiente.
int unset_env_value(t_env **env, const char *key); // Remove uma variável do ambiente.
void free_env_list(t_env *env); // Libera toda a memória da lista de variáveis de ambiente.
void print_env_list(t_env *env); // Imprime todas as variáveis da lista de ambiente no formato `key=value`.
int is_valid_env_key(const char *key); // Verifica se o nome de uma variável de ambiente é válido.
int env_has_key(t_env *env, const char *key); // Retorna 1 se a variável com a chave existe no ambiente.
void add_env_node(t_env **env, char *key, char *value); // Adiciona um novo par chave-valor na lista de ambiente.
t_env *new_env_node(char *key, char *value); // Cria um novo nó de variável de ambiente.
char *safe_strdup(const char *s); // Versão segura de `strdup`, que trata erro de malloc.
void *safe_malloc(size_t size); // Wrapper seguro para `malloc`, com tratamento de erro.
void *safe_calloc(size_t count, size_t size); // Wrapper seguro para `calloc`, com tratamento de erro.
void free_split(char **arr); // Libera um array de strings alocado dinamicamente (`split`).
void print_error(const char *msg); // Mostra uma mensagem de erro padronizada no stderr.
void print_strs(char **arr); // Imprime um array de strings linha por linha.
int ft_strcmp(const char *s1, const char *s2); // Compara duas strings (versão da libft).
int ft_isspace(int c); // Verifica se um caractere é espaço ou tabulação.
int ft_isdigit(int c); // Verifica se um caractere é numérico.
int ft_atoi_strict(const char *str, int *out); // Converte string para int validando se é um número real.
char *ft_strjoin_free(char *s1, char *s2); // Concatena duas strings e libera `s1`.
char *ft_strdup_range(const char *src, int start, int end); // Duplica uma substring entre `start` e `end`.
char *ft_substr(const char *s, int start, int len); // Extrai uma substring com `start` e tamanho `len`.
int count_char(const char *str, char c); // Conta quantas vezes um caractere aparece na string.
int split_len(char **arr); // Retorna o número de elementos de um array de strings.
char *ft_strcpy(char *dst, const char *src); // Copia uma string para outra (como `strcpy`).
char *ft_strncpy(char *dst, const char *src, size_t n); // Copia até `n` caracteres de `src` para `dst`.
void *ft_memcpy(void *dst, const void *src, size_t n); // Copia `n` bytes da memória de `src` para `dst`.
void *ft_memset(void *b, int c, size_t len); // Preenche `len` bytes da memória com o valor `c`.
char *ft_strchr(const char *s, int c); // Retorna ponteiro para o primeiro caractere `c` encontrado em `s`.
void free_shell(t_shell *shell); // Libera todos os recursos alocados pela estrutura `t_shell`.
void free_command(t_cmd *cmd); // Libera a memória de um comando individual.
void free_redirections(t_redir *redir); // Libera todos os redirecionamentos associados a um comando.
void exit_clean(t_shell *shell, int code); // Sai do shell e libera tudo com o código de saída fornecido.
void deep_cleanup_on_error(t_shell *shell); // Realiza uma limpeza completa em caso de erro fatal.
```
