#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <limits>
#include <vector>
#include <iomanip>

using namespace std;

// Função para verificar se os dados já foram cadastrados.
bool dadosJaCadastrados(const vector<string>& dados, const string& nome, const string& matricula, const string& turma) {
    for (const string& linha : dados) {
        istringstream iss(linha);
        string nomeExistente, matriculaExistente, turmaExistente;

        getline(iss, nomeExistente, '|');
        getline(iss, matriculaExistente, '|');
        getline(iss, turmaExistente, '|');

        // Remove espaços em branco das extremidades
        nomeExistente.erase(0, nomeExistente.find_first_not_of(" \t"));
        nomeExistente.erase(nomeExistente.find_last_not_of(" \t") + 1);
        matriculaExistente.erase(0, matriculaExistente.find_first_not_of(" \t"));
        matriculaExistente.erase(matriculaExistente.find_last_not_of(" \t") + 1);
        turmaExistente.erase(0, turmaExistente.find_first_not_of(" \t"));
        turmaExistente.erase(turmaExistente.find_last_not_of(" \t") + 1);

        if (nomeExistente == nome && matriculaExistente == matricula && turmaExistente == turma) {
            return true;
        }
    }
    return false;
}
// Função para validar o nome do aluno
bool nomeValido(const string& nome) {
    if (nome.empty() || nome.length() > 70) return false;
    for (char c : nome) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

// Função para validar a matrícula do aluno.
bool matriculaValida(const string& matricula) {
    if (matricula.empty() || matricula.length() > 14) return false;
    for (char c : matricula) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Função para validar a turma do aluno.
bool turmaValida(const string& turma) {
    return !turma.empty();
}

void adicionarDados(vector<string>& dados) {
    string nome, matricula, turma;
    while (true) {
        cout << "Digite um nome para cadastro (max 70 caracteres): ";
        getline(cin, nome);
        if (nomeValido(nome)) break;
        cout << "NOME INVALIDO. TENTE NOVAMENTE!" << endl;
    }

    while (true) {
        cout << "Digite a sua matricula (max 14 caracteres): ";
        getline(cin, matricula);
        if (matriculaValida(matricula)) break;
        cout << "MATRICULA INVALIDA. TENTE NOVAMENTE!" << endl;
    }

    while (true) {
        cout << "Digite a sua turma: ";
        getline(cin, turma);
        if (turmaValida(turma)) break;
        cout << "TURMA INVALIDA. TENTE NOVAMENTE!" << endl;
    }

    if (dadosJaCadastrados(dados, nome, matricula, turma)) {
        cout << "ERRO: NOME E MATRICULA JA FORAM CADASTRADOS." << endl;
    } else {
        dados.push_back(nome + " | " + matricula + " | " + turma + " |");
        cout << "CONFIRMADO: OS DADOS FORAM CADASTRADOS COM SUCESSO!" << endl;
    }
}

bool isValidDisciplina(const string& disciplina) {
    if (disciplina.empty() || disciplina.length() > 40) return false;
    for (char c : disciplina) {
        if (!isalpha(c) && c != ' ') return false;
    }
    return true;
}

// Função para validar o código da disciplina.
bool isValidCodigo(const string& codigo) {
    if (codigo.empty() || codigo.length() > 5) return false;
    for (char c : codigo) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void adicionarDisciplina(vector<string>& disciplinas) {
    string disciplina, codigo;
    while (true) {
        cout << "Digite uma disciplina para cadastro (max 40 caracteres): ";
        getline(cin, disciplina);
        if (isValidDisciplina(disciplina)) break;
        cout << "DISCIPLINA INVALIDA. TENTE NOVAMENTE!" << endl;
    }

    while (true) {
        cout << "Digite o codigo referente a disciplina (max 5 caracteres): ";
        getline(cin, codigo);
        if (isValidCodigo(codigo)) break;
        cout << "CODIGO INVALIDO. TENTE NOVAMENTE!" << endl;
    }

    for (const string& linha : disciplinas) {
        istringstream iss(linha);
        string disciplinaExistente, codigoExistente;

        getline(iss, disciplinaExistente, '|');
        getline(iss, codigoExistente, '|');

        // Remove espaços em branco das extremidades
        disciplinaExistente.erase(0, disciplinaExistente.find_first_not_of(" \t"));
        disciplinaExistente.erase(disciplinaExistente.find_last_not_of(" \t") + 1);
        codigoExistente.erase(0, codigoExistente.find_first_not_of(" \t"));
        codigoExistente.erase(codigoExistente.find_last_not_of(" \t") + 1);

        if (disciplinaExistente == disciplina && codigoExistente == codigo) {
            cout << "ERRO: DISCIPLINA E CODIGO JA FORAM CADASTRADOS!" << endl;
            return;
        } else if (codigoExistente == codigo) {
            cout << "ERRO: O CODIGO DIGITADO JA PERTENCE A UMA DISCIPLINA!" << endl;
            return;
        }

    }

    disciplinas.push_back(disciplina + " | " + codigo + " |");
    cout << "CONFIRMADO: OS DADOS FORAM CADASTRADOS COM SUCESSO!" << endl;
}

void cadastrarNotas(vector<string>& alunos, vector<string>& disciplinas, vector<vector<float>>& matrizNotas) {
    string matricula;
    string codigo;
    float nota;

    cout << "Alunos disponíveis:\n";
    for (const string& aluno : alunos) {
        istringstream iss(aluno);
        string nome, matriculaExistente, turma;
        getline(iss, nome, '|');
        getline(iss, matriculaExistente, '|');
        getline(iss, turma, '|');
        cout << "Matrícula: " << matriculaExistente << " | Nome: " << nome << endl;
    }

    cout << "\nDisciplinas disponíveis:\n";
    for (const string& disciplina : disciplinas) {
        istringstream iss(disciplina);
        string nomeDisciplina, codigoDisciplina;
        getline(iss, nomeDisciplina, '|');
        getline(iss, codigoDisciplina, '|');
        cout << "Codigo: " << codigoDisciplina << " | Disciplina: " << nomeDisciplina << endl;
    }

    while (true) {
        cout << "\nDigite a matricula do aluno: ";
        getline(cin, matricula);
        bool matriculaEncontrada = false;
        for (size_t i = 0; i < alunos.size(); ++i) {
            istringstream iss(alunos[i]);
            string nome, matriculaExistente, turma;
            getline(iss, nome, '|');
            getline(iss, matriculaExistente, '|');
            getline(iss, turma, '|');
            matriculaExistente.erase(0, matriculaExistente.find_first_not_of(" \t"));
            matriculaExistente.erase(matriculaExistente.find_last_not_of(" \t") + 1);
            if (matriculaExistente == matricula) {
                matriculaEncontrada = true;
                break;
            }
        }
        if (matriculaEncontrada) break;
        cout << "MATRICULA NAO ENCONTRADA. TENTE NOVAMENTE!" << endl;
    }

    while (true) {
        cout << "Digite o código da disciplina: ";
        getline(cin, codigo);
        bool codigoEncontrado = false;
        for (size_t i = 0; i < disciplinas.size(); ++i) {
            istringstream iss(disciplinas[i]);
            string nomeDisciplina, codigoDisciplina;
            getline(iss, nomeDisciplina, '|');
            getline(iss, codigoDisciplina, '|');
            codigoDisciplina.erase(0, codigoDisciplina.find_first_not_of(" \t"));
            codigoDisciplina.erase(codigoDisciplina.find_last_not_of(" \t") + 1);
            if (codigoDisciplina == codigo) {
                codigoEncontrado = true;
                break;
            }
        }
        if (codigoEncontrado) break;
        cout << "CODIGO DA DISCIPLINA NAO ENCONTRADO. TENTE NOVAMENTE!" << endl;
    }

    while (true) {
        cout << "Digite a nota (0 a 10): ";
        cin >> nota;
        if (cin.fail() || nota < 0 || nota > 10) {
            cin.clear(); // Limpa o erro
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta a entrada inválida
            cout << "NOTA INVALIDA. TENTE NOVAMENTE!" << endl;
        } else {
            break;
        }
    }

    // Encontrar o índice do aluno
    size_t alunoIndex = -1;
    for (size_t i = 0; i < alunos.size(); ++i) {
        istringstream iss(alunos[i]);
        string nome, matriculaExistente, turma;
        getline(iss, nome, '|');
        getline(iss, matriculaExistente, '|');
        getline(iss, turma, '|');
        matriculaExistente.erase(0, matriculaExistente.find_first_not_of(" \t"));
        matriculaExistente.erase(matriculaExistente.find_last_not_of(" \t") + 1);
        if (matriculaExistente == matricula) {
            alunoIndex = i;
            break;
        }
    }

    // Encontrar o índice da disciplina
    size_t disciplinaIndex = -1;
    for (size_t i = 0; i < disciplinas.size(); ++i) {
        istringstream iss(disciplinas[i]);
        string nomeDisciplina, codigoDisciplina;
        getline(iss, nomeDisciplina, '|');
        getline(iss, codigoDisciplina, '|');
        codigoDisciplina.erase(0, codigoDisciplina.find_first_not_of(" \t"));
        codigoDisciplina.erase(codigoDisciplina.find_last_not_of(" \t") + 1);
        if (codigoDisciplina == codigo) {
            disciplinaIndex = i;
            break;
        }
    }

    // Ajustar o tamanho da matriz de notas se necessário
    if (alunoIndex >= matrizNotas.size()) {
        matrizNotas.resize(alunoIndex + 1);
    }
    if (disciplinaIndex >= matrizNotas[alunoIndex].size()) {
        matrizNotas[alunoIndex].resize(disciplinaIndex + 1, -1.0f); // Inicializa com -1 para indicar nota não atribuída
    }

    matrizNotas[alunoIndex][disciplinaIndex] = nota;
    cout << "NOTA CADASTRADA COM SUCESSO!" << endl;
}

// Função para gerar relatório.
void gerarRelatorio(const vector<string>& alunos, const vector<string>& disciplinas, const vector<vector<float>>& matrizNotas) {
    cout << fixed << setprecision(2);
    cout << "RELATORIO DE NOTAS:\n";
    cout << "---------------------------------------------------\n";
    cout << left << setw(20) << "Aluno" << setw(20) << "Disciplina" << "Nota" << endl;
    cout << "---------------------------------------------------\n";

    for (size_t i = 0; i < alunos.size(); ++i) {
        istringstream issAluno(alunos[i]);
        string nomeAluno, matricula, turma;
        getline(issAluno, nomeAluno, '|');
        getline(issAluno, matricula, '|');
        getline(issAluno, turma, '|');

        for (size_t j = 0; j < disciplinas.size(); ++j) {
            istringstream issDisciplina(disciplinas[j]);
            string nomeDisciplina, codigoDisciplina;
            getline(issDisciplina, nomeDisciplina, '|');
            getline(issDisciplina, codigoDisciplina, '|');

            if (j < matrizNotas[i].size()) {
                float nota = matrizNotas[i][j];
                if (nota > 0) {
                    cout << left << setw(20) << nomeAluno << setw(20) << nomeDisciplina << nota << endl;
                }
            }
        }
    }
    cout << "---------------------------------------------------\n";
}

// Função para carregar dados de um arquivo para um vetor de strings.
void carregarDados(const string& nomeArquivo, vector<string>& dados) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO " << nomeArquivo << endl;
        return;
    }

    dados.clear();
    string linha;
    while (getline(arquivo, linha)) {
        dados.push_back(linha);
    }

    arquivo.close();
}

// Função para salvar dados de um vetor de strings em um arquivo.
void salvarDados(const string& nomeArquivo, const vector<string>& dados) {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO " << nomeArquivo << endl;
        return;
    }

    for (const string& linha : dados) {
        arquivo << linha << endl;
    }

    arquivo.close();
}

// Função para salvar a matriz de notas em um arquivo.
void salvarMatrizNotas(const string& nomeArquivo, const vector<vector<float>>& matrizNotas) {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO " << nomeArquivo << endl;
        return;
    }

    for (const vector<float>& linha : matrizNotas) {
        for (float nota : linha) {
            if (nota >= 0) { 
                arquivo << nota << " ";
            } else {
                arquivo << " "; // Adiciona um espaço para manter a formatação
            }
        }
        arquivo << endl;
    }

    arquivo.close();
}

// Função para carregar a matriz de notas a partir de um arquivo.
void carregarMatrizNotas(const string& nomeArquivo, vector<vector<float>>& matrizNotas) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "ERRO: NAO FOI POSSIVEL ABRIR O ARQUIVO " << nomeArquivo << endl;
        return;
    }

    matrizNotas.clear();
    string linha;
    while (getline(arquivo, linha)) {
        istringstream iss(linha);
        vector<float> notas;
        float nota;
        while (iss >> nota) {
            notas.push_back(nota);
        }
        matrizNotas.push_back(notas);
    }

    arquivo.close();
}

// Função para consultar notas de um aluno.
void consultarNotasAluno(const vector<string>& alunos, const vector<string>& disciplinas, const vector<vector<float>>& matrizNotas) {
    string matricula;
    cout << "Matricula do aluno: ";
    getline(cin, matricula);

    int aluno_index = -1;
    for (size_t i = 0; i < alunos.size(); i++) {
        istringstream iss(alunos[i]);
        string nome, matriculaExistente, turma;
        getline(iss, nome, '|');
        getline(iss, matriculaExistente, '|');
        getline(iss, turma, '|');
        matriculaExistente.erase(0, matriculaExistente.find_first_not_of(" \t"));
        matriculaExistente.erase(matriculaExistente.find_last_not_of(" \t") + 1);
        if (matriculaExistente == matricula) {
            aluno_index = i;
            break;
        }
    }

    if (aluno_index == -1) {
        cout << "Aluno nao encontrado." << endl;
        return;
    }

    cout << "Notas de " << alunos[aluno_index] << ":" << endl;
    for (size_t i = 0; i < disciplinas.size(); i++) {
        if (i < matrizNotas[aluno_index].size()) {
            cout << left << setw (10) << disciplinas[i] << ": " << matrizNotas[aluno_index][i] << endl;
        }
    }
}

void calcularMedias(const vector<string>& alunos, const vector<string>& disciplinas, const vector<vector<float>>& matrizNotas) {
    if (alunos.empty() || disciplinas.empty()) {
        cout << "Não há dados suficientes para calcular médias." << endl;
        return;
    }

    cout << fixed << setprecision(2);
    for (size_t i = 0; i < alunos.size(); ++i) {
        float soma = 0;
        int count = 0; 

        for (size_t j = 0; j < disciplinas.size(); ++j) {
            if (j < matrizNotas[i].size() && matrizNotas[i][j] >= 0) {
                soma += matrizNotas[i][j];
                ++count;
            }
        }

        float media_geral = count > 0 ? soma / count : 0;
        istringstream iss(alunos[i]);
        string nomeAluno, matricula, turma;
        getline(iss, nomeAluno, '|');
        cout << "Media geral de " << nomeAluno << ": " << media_geral << endl;
    }
}

void criarArquivosVazios() {
    // Tenta criar arquivos vazios
    ofstream arquivo("alunos.txt", ios::trunc); 
    arquivo.close();
    arquivo.open("disciplinas.txt", ios::trunc); 
    arquivo.close();
    arquivo.open("notas.txt", ios::trunc); 
    arquivo.close();
}


int main() {
    vector<string> alunos;
    vector<string> disciplinas;
    vector<vector<float>> matrizNotas;

    criarArquivosVazios();

    carregarDados("alunos.txt", alunos);
    carregarDados("disciplinas.txt", disciplinas);
    carregarMatrizNotas("notas.txt", matrizNotas);

    int opcao;

    do {
        cout << "\nEscolha uma opcao:\n";
        cout << "1. Cadastrar Alunos\n";
        cout << "2. Cadastrar Disciplinas\n";
        cout << "3. Cadastrar Notas\n";
        cout << "4. Consultar notas\n";
        cout << "5. Calcular medias\n";
        cout << "6. Gerar Relatorio\n";
        cout << "0. Sair\n";
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar o buffer de entrada

        switch (opcao) {
            case 1:
                adicionarDados(alunos);
                salvarDados("alunos.txt", alunos);
                break;
            case 2:
                adicionarDisciplina(disciplinas);
                salvarDados("disciplinas.txt", disciplinas);
                break;
            case 3:
                cadastrarNotas(alunos, disciplinas, matrizNotas);
                salvarMatrizNotas("notas.txt", matrizNotas);
                break;
            case 4:
                consultarNotasAluno(alunos, disciplinas, matrizNotas);
                break;
            case 5:
                calcularMedias(alunos,disciplinas,matrizNotas);
            case 6:
                gerarRelatorio(alunos, disciplinas, matrizNotas);
                break;
            case 0:
                cout << "Saindo do programa..." << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    } while (opcao != 0);

    return 0;
}
