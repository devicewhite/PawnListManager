# List Manager 

Este projeto contém um conjunto de funções para manipulação de listas, permitindo adicionar, remover e gerenciar valores.

## Importância

As listas são estruturas de dados fundamentais em programação. Elas permitem armazenar múltiplos itens em uma única variável, oferecendo uma maneira organizada de acessar e manipular dados. As funções aqui apresentadas fornecem uma interface simples e eficiente para realizar operações comuns em listas, como inserções, remoções e buscas.

> [!Note]
> Caso encontre falhas ou tenha sugestões de otimização, por favor, faça um Pull Request no repositório!

---

# Funções Disponíveis

## 1. **List_PushFront(list, value)**
Adiciona um valor ao início da lista.

## 2. **List_PushBack(list, value)**
Adiciona um valor ao final da lista.

## 3. **List_Insert(list, index, value)**
Insere um valor em um índice específico da lista.

## 4. **List_PopFront(list)**
Remove e retorna o valor do início da lista.

## 5. **List_PopBack(list)**
Remove e retorna o valor do final da lista.

## 6. **List_Remove(list, index)**
Remove e retorna o valor de um índice específico da lista.

## 7. **List_PopFrontEx(list, &value)**
Remove o valor do início da lista e o armazena na variável.

## 8. **List_PopBackEx(list, &value)**
Remove o valor do final da lista e armazena na variável.

## 9. **List_RemoveEx(list, index, &value)**
Remove o valor de um índice específico da lista e armazena na variável.

## 10. **List_Sort(list)**
Ordena a lista em ordem crescente.

## 11. **List_Reverse(list)**
Inverte a ordem dos valores na lista.

## 12. **List_Clear(list)**
Limpa todos os valores da lista.

## 13. **List_FindValue(list, value)**
Retorna o índice de um valor específico na lista.

## 14. **List_SetValue(list, index, value)**
Define um valor de um índice específico da lista.

## 15. **List_GetValue(list, index)**
Retorna um valor de um índice específico da lista.

## 16. **List_FindValueEx(list, value, &index)**
Encontra um valor na lista e armazena seu índice na variável.

## 17. **List_GetValueEx(list, index, &value)**
Obtém um valor de um índice específico e o armazena na variável.

## 18. **List_Count(list)**
Retorna a quantidade de elementos na lista.

## 19. **List_IsEmpty(list)**
Verifica se a lista está vazia.

## 20. **List_IsFull(list)**
Verifica se a lista está cheia.

## 21. **List_Contains(list, value)**
Verifica se a lista contém um valor específico.

---

# Macros Disponíveis

## 1. **ListManager**
Cria uma nova lista.

Exemplo:

```pawn
new ListManager:myList<10>;
```

## 2. **List_ForEach**
Itera sobre todos os elementos da lista.

Exemplo:

```pawn
List_ForEach(i;myList;0)
{
    printf("Valor: %d, Indice: %d", i, __idx);
}
```

---

# Listas Disponíveis

## 1. **Actors**
Armazena todos os id's de atores do servidor.

## 2. **NPCs**
Armazena todos os id's de npc's do servidor.

## 3. **Players**
Armazena todos os id's de jogadores do servidor.

## 4. **Vehicles**
Armazena todos os id's de veículos do servidor.

---

Este pequeno projeto foi elaborado por [DeviceBlack](https://github.com/devicewhite).

Espero que façam bom proveito deste projeto de armazenamento de dados em arrays!
