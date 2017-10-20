

#include <iostream>
#include <vector>
#include <sstream>
#define INF 0xFFFFFFFF


using namespace std;


unsigned VmaxNum = 0; // the number of vertices
vector<unsigned> Vertex; // save vertices
vector<vector<unsigned> > matrix;
vector<unsigned> print_path;


bool s_vertices(unsigned V1, unsigned V2); //assign matrix value (1)
bool get_path(unsigned v_start, unsigned v_end); // search shortest path


//set the vertices vector

void set_ver(unsigned num) {//define 0~14 vertices in vector & define resize matrix and assign INF
    //clear data
    print_path.clear();
    Vertex.clear();
    matrix.clear();


    VmaxNum = num;
    for (unsigned i = 0; i < VmaxNum; i++) {
        Vertex.push_back(i);
    }// define all vertices


    //define resize matrix and assign INF
    matrix.resize(VmaxNum);
    /*
    for (auto &i:matrix){
        i.resize(VmaxNum,INF);
    }*/

    for (vector<vector<unsigned> >::iterator _first = matrix.begin();
            _first != matrix.end(); _first++) {
        (*_first).resize(VmaxNum, INF);
    }

}

//define matrix and assign 1

bool s_vertices(unsigned V1, unsigned V2) {
    if (V1 >= VmaxNum || V2 >= VmaxNum) {
        return false;
    } else {
        matrix[V1][V2] = 1;
        matrix[V2][V1] = 1;
    }
    return true;
}


//define the shortest path

bool get_path(unsigned v_start, unsigned v_end) {
    unsigned i, j, m, k;
    unsigned min;
    unsigned prev[VmaxNum];
    unsigned dist[VmaxNum];
    unsigned new_dist;
    print_path.clear();
    int flag[VmaxNum]; // flag[i]=1表示"顶点vs"到"顶点i"的最短路径已成功获取。
    if (v_start >= VmaxNum || v_end >= VmaxNum) {
        return false;
    }
    // 初始化
    for (i = 0; i < VmaxNum; i++) {
        flag[i] = 0; // 顶点i的最短路径还没获取到。
        prev[i] = 0; // 顶点i的前驱顶点为0。
        dist[i] = matrix[v_start][i]; // 顶点i的最短路径为"顶点vs"到"顶点i"的权。
    }

    // 对"顶点vs"自身进行初始化
    flag[v_start] = 1;
    dist[v_start] = 0;

    // 遍历mVexNum-1次；每次找出一个顶点的最短路径。
    for (i = 1; i < VmaxNum; i++) {
        // 寻找当前最小的路径；
        // 即，在未获取最短路径的顶点中，找到离vs最近的顶点(k)。
        min = INF;
        for (j = 0; j < VmaxNum; j++) {
            if (flag[j] == 0 && dist[j] < min) {
                min = dist[j];
                k = j;
            }
        }
        // 标记"顶点k"为已经获取到最短路径
        if (j == VmaxNum) {
            return false;
        }
        flag[k] = 1;

        // 修正当前最短路径和前驱顶点
        // 即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j < VmaxNum; j++) {
            new_dist = (matrix[k][j] == INF ? INF : (min + matrix[k][j]));
            if (flag[j] == 0 && (new_dist < dist[j])) {
                dist[j] = new_dist;
                prev[j] = k;
            }
        }
    }
    print_path.push_back(v_end);

    //trace back (prev, Vstart,Vend)
    unsigned vertex = v_end;
    while (dist[vertex] > 0) {
        for (m = 0; m < VmaxNum; m++) {
            if (dist[m] + 1 == dist[vertex]) {
                vertex = m;
                print_path.push_back(vertex);
                break;
            }

        }
    }

    if (print_path.size() <= 1) {
        return false;
    }

    for (vector<unsigned >::iterator m = print_path.begin(); m != print_path.end(); m++) //用迭代器的方式输出容器对象的值
    {
        cout << *m;
        if (m != print_path.end() - 1) {
            cout << "-";
        } else
            cout << endl;

    }
    return true;
}

int main(int argc, char ** argv) {
    // define variables
    char command = '0';
    unsigned VmaxNum;
    std::string EdgeString;
    unsigned Vstart, Vend;
    unsigned Ver;


    // read from stdin until EOF
    while (!std::cin.eof()) {
        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);
        std::istringstream input(line);

        while (!input.eof()) {
            //read the first charaster
            char character;
            input >> character;
            if (input.fail()) {
                std::cerr << "Error first character\n";
                break;
            } else {
                command = character;
            }

            switch (command) {
                case 'V':
                    input >> VmaxNum;
                    set_ver(VmaxNum);
                    break;

                case 'E':
                {
                    input >> EdgeString;
                    std::istringstream EdgeInput(EdgeString);
                    char ch;
                    unsigned V1, V2;
                    EdgeInput >> ch;
                    // read '{'
                    if (EdgeInput.fail()) {
                        std::cerr << "Error Character\n";
                        break;
                    }
                    while (ch != '}') {
                        EdgeInput >> ch; // read '<'
                        if (EdgeInput.fail()) {
                            std::cerr << "Error Character\n";
                            break;
                        }
                        EdgeInput >> Ver; // read V1(first V)
                        if (EdgeInput.fail()) {
                            std::cerr << "Error Character\n";
                            break;
                        }
                        V1 = Ver; //save V
                        EdgeInput >> ch; // read ','
                        if (EdgeInput.fail()) {
                            std::cerr << "Error Character\n";
                            break;
                        }
                        EdgeInput >> Ver; // read V2(second V)
                        if (EdgeInput.fail()) {
                            std::cerr << "Error Character\n";
                            break;
                        }
                        V2 = Ver; //save V
                        if (s_vertices(V1, V2) == false) { //create a matrix
                            std::cerr << "Error: Wrong id" << std::endl;
                            break;
                        }
                        EdgeInput >> ch; // read '>'
                        if (EdgeInput.fail()) {
                            std::cerr << "Error Character\n";
                            break;
                        }
                        EdgeInput >> ch; // read ',' or '}'
                        if (EdgeInput.fail()) {
                            std::cerr << "Error Character\n";
                            break;
                        }
                    }
                    break;
                }
                case 's':
                {
                    input >> Vstart >> Vend;
                    if (get_path(Vend, Vstart) == false) { // get a reversed vector
                        std::cerr << "Error: Path Error" << std::endl;
                    }
                    break;
                }
                default:
                {
                    std::cout << "Error: Wrong Command!" << std::endl;
                    break;
                }

            }


        }

    }
    return 0;

}

/*
V 15
E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}
s 2 10

V 5
E {<0,2>,<2,1>,<2,3>,<3,4>,<4,1>}
s 4 0

 * E {<2,3>,<3,4>,<4,7>,<1,5>,<5,6>,<6,7>}
 */


