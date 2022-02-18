#include <iostream>

// 블럭의 모양은 테트리스 나무위키
//(https://namu.wiki/w/%ED%85%8C%ED%8A%B8%EB%A6%AC%EC%8A%A4/%EC%9A%A9%EC%96%B4)
// 를 참고하였습니다.

// 1번 블럭 : I미노
const int block1[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0}
};
// 2번 블럭 : O미노
const int block2[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};
// 3번 블럭 : Z미노
const int block3[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 0}
};
// 4번 블럭 : S미노
const int block4[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};
// 5번 블럭 : J미노
const int block5[4][4] = {
    {0, 0, 1, 0},
    {0, 0, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};
// 6번 블럭 : L미노
const int block6[4][4] = {
    {0, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};
// 7번 블럭 : T미노
const int block7[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 1},
    {0, 0, 1, 0},
    {0, 0, 0, 0}
};

class Map {
    private:
    public:
    /*int map[][] = {}; // n * n 그리드 초기화 어케 하지 ㅠㅠ 
    Map(int n)  {
        width = n;
        height = n;
        // 배열 동적 할당 << 이게 맞나?
        int** map = (int**)malloc(sizeof(int*) * width);
        for (int i = 0; i < width; i++) { 
            map[i] = (int*)malloc(sizeof(int) * height); 
        }
    }*/
    int map[20][10] =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    void show_map();
    /*int get_width() { return width; }
    int get_height() { return height; }*/ // getter
};

void Map::show_map() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (map[i][j]) std::cout << "■";
            else std::cout << "□";
        }
        std::cout << std::endl;
    }
}

class Block {
    protected: // 자식에서 수정해야하므로 protected
    int shape[4][4] = // 블록의 모양
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    };
    int x; // x죄표
    int y; // y좌표
    public:
    void show_block(); // 잘 안 쓰일 듯... 그저 모양이 잘 나오는지 디버깅 용
    void make_block(Map* map); // 맵에 블럭 얹기
    void rotate_block(int d); // i = 0: 반시계 회전, i = 1: 시계 회전
};

void Block::show_block() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j]) std::cout << "■";
            else std::cout << "□";
        }
        std::cout << std::endl;
    }
}

void Block::make_block(Map* _map) {
    x = 0;
    y = 3;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            (*_map).map[x + i][y + j] += shape[i][j]; // 맵에 블럭 그리기 (원소 더하기)
        }
    }
}

void Block::rotate_block(int d) {
    int temp[4][4];
    if (d) { // 시계 회전
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[i][j] = shape[3 - j][i];
            }
        }
    } else { // 반시계 회전
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                temp[i][j] = shape[j][3 - i];
            }
        }
    }
    // 모양 베끼기
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shape[i][j] = temp[i][j];
        }
    }
}

class Block1 : public Block {
    public:
    Block1() {
        // 모양 베끼기
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = block1[i][j];
            }
        }
    }
};

class Block2 : public Block {
    public:
    Block2() {
        // 모양 베끼기
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = block2[i][j];
            }
        }
    }
};

class Block3 : public Block {
    public:
    Block3() {
        // 모양 베끼기
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = block3[i][j];
            }
        }
    }
};

class Block4 : public Block {
    public:
    Block4() {
        // 모양 베끼기
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = block4[i][j];
            }
        }
    }
};

class Block5 : public Block {
    public:
    Block5() {
        // 모양 베끼기
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = block5[i][j];
            }
        }
    }
};

class Block6 : public Block {
    public:
    Block6() {
        // 모양 베끼기
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = block6[i][j];
            }
        }
    }
};

class Block7 : public Block {
    public:
    Block7() {
        // 모양 베끼기
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                shape[i][j] = block7[i][j];
            }
        }
    }
};

int main() {
    // 맵을 생성하고, block 4를 생성, 맵 보여주기
    Map map;
    Block4 block_4;
    block_4.make_block(&map);
    map.show_map();

    // 블럭의 회전 알고리즘이 잘 작동되는지 확인 [이상 무]
    /*Block4 block_4;
    std::cout << "block1" << std::endl;
    block_1.show_block();
    block_1.rotate_block(0);
    block_1.show_block();
    block_1.rotate_block(1);
    block_1.show_block();
    block_1.rotate_block(1);
    block_1.show_block();*/

    return 0;
}