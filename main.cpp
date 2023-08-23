#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <locale.h>
using namespace std;

struct Organizacao
{
    string nome;
    float numeroDeCiclos = 0;
    float numeroDeInstrucoes = 0;
    float frequenciaDeClock;
    float tempoExec;
};

char definirTipoDaInstrucao(string linha)
{
    string ultimos7Numeros = linha.substr(linha.size() - 7);

    if (ultimos7Numeros == "0110111" || ultimos7Numeros == "0010111") // instru��o do tipo U
        return 'U';

    if (ultimos7Numeros == "1101111")
        return 'J';

    if (ultimos7Numeros == "1100111" || ultimos7Numeros == "0010011" || ultimos7Numeros == "0001111" || ultimos7Numeros == "1110011")
        return 'I';

    if (ultimos7Numeros == "1100011")
        return 'B';

    if (ultimos7Numeros == "0000011")
        return 'L';

    if (ultimos7Numeros == "0100011")
        return 'S';

    if (ultimos7Numeros == "0110011")
        return 'R';

    else
    {
        cout << "Erro na instru��o! Verifique o arquivo.";
    }
}

void adicionarNumeroDeCiclosDaOrganizacao(Organizacao &organizacao, char instrucao)
{

    if (organizacao.nome == "A" || organizacao.nome == "a")
    {
        switch (instrucao)
        {
        case 'U':
            organizacao.numeroDeCiclos += 4;
            break;

        case 'J':
            organizacao.numeroDeCiclos += 3;
            break;

        case 'I':
            organizacao.numeroDeCiclos += 4;
            break;

        case 'B':
            organizacao.numeroDeCiclos += 3;
            break;

        case 'L':
            organizacao.numeroDeCiclos += 5;
            break;

        case 'S':
            organizacao.numeroDeCiclos += 4;
            break;

        case 'R':
            organizacao.numeroDeCiclos += 4;
            break;

        default:
            break;
        }
    }

    if (organizacao.nome == "B" || organizacao.nome == "b")
    {
        switch (instrucao)
        {
        case 'U':
            organizacao.numeroDeCiclos += 5;
            break;

        case 'J':
            organizacao.numeroDeCiclos += 5;
            break;

        case 'I':
            organizacao.numeroDeCiclos += 5;
            break;

        case 'B':
            organizacao.numeroDeCiclos += 5;
            break;

        case 'L':
            organizacao.numeroDeCiclos += 5;
            break;

        case 'S':
            organizacao.numeroDeCiclos += 5;
            break;

        case 'R':
            organizacao.numeroDeCiclos += 5;
            break;

        default:
            break;
        }
    }
}

void calcularCiclosDeInstrucao(Organizacao &organizacao)
{
    ifstream arquivo;
    string linha;
    char instrucao;

    if (organizacao.nome == "A" || organizacao.nome == "a")
    {
        arquivo.open("ArquivosCPU1/DumpInstrucoes.txt");
        cout << "Arquivo Dump da organiza��o A: " << endl;
        while (getline(arquivo, linha))
        {
            instrucao = definirTipoDaInstrucao(linha);
            adicionarNumeroDeCiclosDaOrganizacao(organizacao, instrucao);
            organizacao.numeroDeInstrucoes++;
            cout << linha << endl; // para testes
        }
    }

    else
    {
        arquivo.open("ArquivosCPU2/DumpInstrucoes.txt");
        cout << endl
             << endl
             << "Arquivo Dump da organiza��o B: " << endl;
        while (getline(arquivo, linha))
        {
            instrucao = definirTipoDaInstrucao(linha);
            adicionarNumeroDeCiclosDaOrganizacao(organizacao, instrucao);
            organizacao.numeroDeInstrucoes++;
            cout << linha << endl; // para testes
        }
    }

    cout << endl
         << endl;
    arquivo.close();
}

void informarClock(Organizacao &organizacao)
{
    cout << "Qual � a frequ�cia de clock da organiza��o " << organizacao.nome << "? (em Ghz) " << endl;
    cin >> organizacao.frequenciaDeClock;
}

void calcularTempoExec(Organizacao &organizacao)
{
    organizacao.tempoExec = (organizacao.numeroDeCiclos / organizacao.frequenciaDeClock);
}

char calcularDesempenho(Organizacao &organizacaoA, Organizacao &organizacaoB)
{
    float desempenho = (organizacaoA.tempoExec / organizacaoB.tempoExec);
    char melhorDesempenho;

    if (desempenho > 1)
    {
        melhorDesempenho = 'B';
    }
    if (desempenho < 1)
    {
        melhorDesempenho = 'A';
    }
    if (desempenho == 1)
    {
        melhorDesempenho = 'C'; // pra usar dps na hora de imprimir que s�o iguais
    }
    return melhorDesempenho;
}

float mostrarCPIMedio(Organizacao organizacao)
{
    float cpi = (organizacao.numeroDeCiclos / organizacao.numeroDeInstrucoes);

    return cpi;
}

float mostrarDesempenho(Organizacao organizacao)
{
    return organizacao.tempoExec;
}

float mostrarQuaoMaisRapido(Organizacao organizacaoMaisRapida, Organizacao organizacaoMaisLenta)
{
    return (organizacaoMaisLenta.tempoExec / organizacaoMaisRapida.tempoExec);
}

void resultado(Organizacao organizacaoMaisRapida, Organizacao organizacaoMaisLenta)
{
    cout << "A organiza��o " << organizacaoMaisRapida.nome << " � mais r�pida que a organiza��o " << organizacaoMaisLenta.nome << "!" << endl
         << endl;

    cout << "Organiza��o " << organizacaoMaisRapida.nome << ": " << endl;
    cout << "N�mero de ciclos totais gastos executando o progama: " << organizacaoMaisRapida.numeroDeCiclos << endl;
    cout << "CPI m�dio do programa: " << mostrarCPIMedio(organizacaoMaisRapida) << endl;
    cout << "Desempenho final (1/Tempo de execu��o): " << mostrarDesempenho(organizacaoMaisRapida) << endl;

    cout << endl
         << endl;

    cout << "Organiza��o " << organizacaoMaisLenta.nome << ": " << endl;
    cout << "N�mero de ciclos totais gastos executando o progama: " << organizacaoMaisLenta.numeroDeCiclos << endl;
    cout << "CPI m�dio do programa: " << mostrarCPIMedio(organizacaoMaisLenta) << endl;
    cout << "Desempenho final (1/Tempo de execu��o): " << mostrarDesempenho(organizacaoMaisLenta) << endl;

    cout << endl
         << endl;

    cout << "A organiza��o " << organizacaoMaisRapida.nome << " � " << mostrarQuaoMaisRapido(organizacaoMaisRapida, organizacaoMaisLenta) << " vezes mais r�pida que a organiza��o " << organizacaoMaisLenta.nome << "!" << endl
         << endl;
}

void resultadoIgual(Organizacao organizacaoA, Organizacao organizacaoB)
{
    cout << "As duas organiza��es possuem o mesmo desempenho!" << endl
         << endl;

    cout << "Organiza��o " << organizacaoA.nome << ": " << endl;
    cout << "N�mero de ciclos totais gastos executando o progama: " << organizacaoA.numeroDeCiclos << endl;
    cout << "CPI m�dio do programa: " << mostrarCPIMedio(organizacaoA) << endl;
    cout << "Desempenho final (Tempo de execu��o): " << mostrarDesempenho(organizacaoA) << endl;

    cout << endl
         << endl;

    cout << "Organiza��o " << organizacaoB.nome << ": " << endl;
    cout << "N�mero de ciclos totais gastos executando o progama: " << organizacaoB.numeroDeCiclos << endl;
    cout << "CPI m�dio do programa: " << mostrarCPIMedio(organizacaoB) << endl;
    cout << "Desempenho final (Tempo de execu��o): " << mostrarDesempenho(organizacaoB) << endl;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    char melhorCpu;
    Organizacao organizacaoA;
    organizacaoA.nome = "A";
    Organizacao organizacaoB;
    organizacaoB.nome = "B";

    calcularCiclosDeInstrucao(organizacaoA);
    calcularCiclosDeInstrucao(organizacaoB);
    informarClock(organizacaoA);
    informarClock(organizacaoB);

    calcularTempoExec(organizacaoA);
    calcularTempoExec(organizacaoB);

    melhorCpu = calcularDesempenho(organizacaoA, organizacaoB);

    if (melhorCpu == 'B')
    {
        resultado(organizacaoB, organizacaoA);
    }
    else if (melhorCpu == 'A')
    {
        resultado(organizacaoA, organizacaoB);
    }
    else if (melhorCpu == 'C')
    {
        resultadoIgual(organizacaoA, organizacaoB);
    }

    return 0;
}
