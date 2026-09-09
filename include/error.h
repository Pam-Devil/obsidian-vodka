/* c_assert é um padrão de verificação de invariantes inspirado no power10 dos arquivos da NASA
para desenvolvimento de software seguro e crítico.
A proposta é utilizar assertions para garantir que a aplicação não esteja em um estado inválido
E caso entre em estado invalido, que medidas devem ser tomadas além do despejo em stderr 
Assertions não devem produzir efeitos colaterais e definidas como testes booleanos
Quando uma Assertion falha é necessário tomar uma medida de recuperação explicita,
por exemplo retornar uma condição de erro para o chamador da função que executou a assertion que falhou.
*/
#pragma once

#define c_assert(e) ((e) ? true : ((void)fprintf(stderr, "%s:%d: assertion '%s' failed\n", __FILE__, __LINE__, #e), false))

typedef enum
{
    SUCCESS,
    ERROR
} Error;