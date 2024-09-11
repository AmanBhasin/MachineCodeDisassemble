#include "bits/stdc++.h"
using namespace std;

typedef struct Instruction
{
    string insType;
    string dest;
    string src1;
    string src2;

    // make a constructor
} Instruction;

vector<Instruction> parseAssemblyFile(const string &filename)
{
    vector<Instruction> instructions;
    ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return instructions;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue; // Skip empty lines
        }

        // Split the line into components
        istringstream iss(line);
        string instruction, dest, src1, src2;
        iss >> instruction >> dest >> src1 >> src2;

        // Create an Instruction object and add it to the list
        Instruction instr;
        instr.insType = instruction;
        instr.dest = dest;
        instr.src1 = src1;
        instr.src2 = src2;
        instructions.push_back(instr);
    }

    file.close();
    return instructions;
}
// list of instruction objects we will get
// now
void InsertNops(vector<Instruction> &instructions)
{
    int cycle_counter = 0;
    int nops = 0;
    map<string, int> whenFree;
    // register ka free time note => cycleCounter
    if (instructions[0].insType != "ld")
    {
        if (instructions[0].dest != "")
            whenFree[instructions[0].dest] = 3;
        if (instructions[0].src1 != "")
            whenFree[instructions[0].src1] = 2;
        if (instructions[0].src2 != "")
            whenFree[instructions[0].src2] = 2;
    }
    else
    {
        whenFree[instructions[0].dest] = 4;
        int pos = instructions[0].src1.size() - 2;

        whenFree[(instructions[0].src1).substr(pos)] = 2;
    }

    cout << instructions[0].insType << " " << instructions[0].dest << " " << instructions[0].src1 << " " << instructions[0].src2 << endl;

    for (int i = 1; i < instructions.size(); i++)
    {

        Instruction curr_ins = instructions[i];
        Instruction prev_ins = instructions[i - 1];

        if (curr_ins.insType != "ld")
        {
            string curr_dest = curr_ins.dest;
            string curr_src1 = curr_ins.src1;
            string curr_src2 = curr_ins.src2;

            string prev_dest = prev_ins.dest;
            string prev_src1 = prev_ins.src1;
            string prev_src2 = prev_ins.src2;

            // should add nops??
            int calc_dest = i + nops + 3;
            int calc_src1 = i + nops + 2;
            int calc_src2 = i + nops + 2;

            if (whenFree[curr_dest] > calc_dest)
            {
                int diff = whenFree[curr_dest] - calc_dest;
                nops += diff;
                for (int i = 0; i < diff; i++)
                {
                    cout << "NOPS" << endl;
                }
                whenFree[curr_src1] = max(whenFree[curr_src1], calc_src1 + diff);
                whenFree[curr_src2] = max(whenFree[curr_src2], calc_src2 + diff);
            }

            else if (whenFree[curr_src1] > calc_src1)
            {
                int diff = whenFree[curr_src1] - calc_src1;
                nops += diff;
                for (int i = 0; i < diff; i++)
                {
                    cout << "NOPS" << endl;
                }
                whenFree[curr_dest] = max(whenFree[curr_dest], calc_dest + diff);
                whenFree[curr_src2] = max(whenFree[curr_src2], calc_src2 + diff);
            }

            else if (whenFree[curr_src2] > calc_src2)
            {
                int diff = whenFree[curr_src2] - calc_src2;
                nops += diff;
                for (int i = 0; i < diff; i++)
                {
                    cout << "NOPS" << endl;
                }
                whenFree[curr_dest] = max(whenFree[curr_dest], calc_dest + diff);
                whenFree[curr_src1] = max(whenFree[curr_src1], calc_src1 + diff);
            }

            else
            {
            }

            cout << curr_ins.insType << " " << curr_dest << " " << curr_src1 << " " << curr_src2 << endl;
        }

        else
        {
            string curr_dest = curr_ins.dest;
            string curr_src1 = curr_ins.src1;
            string curr_src2 = curr_ins.src2;

            string prev_dest = prev_ins.dest;
            string prev_src1 = prev_ins.src1;
            string prev_src2 = prev_ins.src2;

            // should add nops??
            int calc_dest = i + nops + 4;
            int calc_src1 = i + nops + 2;
            int calc_src2 = i + nops + 2;

            if (whenFree[curr_dest] > calc_dest)
            {
                int diff = whenFree[curr_dest] - calc_dest;
                nops += diff;
                for (int i = 0; i < diff; i++)
                {
                    cout << "NOPS" << endl;
                }
                whenFree[curr_src1] = max(whenFree[curr_src1], calc_src1 + diff);
                whenFree[curr_src2] = max(whenFree[curr_src2], calc_src2 + diff);
            }

            else if (whenFree[curr_src1] > calc_src1)
            {
                int diff = whenFree[curr_src1] - calc_src1;
                nops += diff;
                for (int i = 0; i < diff; i++)
                {
                    cout << "NOPS" << endl;
                }
                whenFree[curr_dest] = max(whenFree[curr_dest], calc_dest + diff);
                whenFree[curr_src2] = max(whenFree[curr_src2], calc_src2 + diff);
            }

            else if (whenFree[curr_src2] > calc_src2)
            {
                int diff = whenFree[curr_src2] - calc_src2;
                nops += diff;
                for (int i = 0; i < diff; i++)
                {
                    cout << "NOPS" << endl;
                }
                whenFree[curr_dest] = max(whenFree[curr_dest], calc_dest + diff);
                whenFree[curr_src1] = max(whenFree[curr_src1], calc_src1 + diff);
            }

            else
            {
            }

            cout << curr_ins.insType << " " << curr_dest << " " << curr_src1 << " " << curr_src2 << endl;
        }
    }

    cout << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Number of Cycles: " << nops + instructions.size() + 4 << endl;
}

int main()
{
    vector<Instruction> ins = parseAssemblyFile("input.txt");
    InsertNops(ins);
}