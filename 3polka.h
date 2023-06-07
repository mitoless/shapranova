#include <cmath>

using namespace std;
struct Stack {
    double number;
    char znak;
    Stack * next;
};
int sch_apl = 0;

Stack *top1, *top2;
void push(Stack * &top, double num, char znk) {
    Stack *p = (Stack *)malloc(sizeof(Stack));
    (*p).number = num;
    (*p).znak = znk;
    (*p).next = top;
    top = p;
}

Stack pop(Stack * &p) {
    Stack temp = *p;
    p = (*p).next;
    return temp;
}

int prior(char ch) {
    if (ch == '(')
        return 0;
    if (ch == '+' || ch == '-') {
        return 1;
    }
    if (ch == '/' || ch == '*') {
        return 2;
    }
    if (ch == '^')
        return 3;
    if (ch == 'S' || ch == 'C' || ch == 'T' || ch == 'L' || ch == 'K') {
        return 5;
    }
}

void replace_F (string& s, string ss, string z){
    int pos = s.find(z);
    while (pos != string::npos) {
        s.replace(pos, z.size(), ss);
        pos = s.find(z);
    }
}

void apply(char znak) {
    double a = pop(top1).number;
    double b;
    if (znak == '-' || znak == '+' || znak == '*' || znak == '/' || znak == '^') {
        b = pop(top1).number;
    }
    if (znak == '-') {
        push(top1, b-a, '@');
    }
    if (znak == '+') {
        push(top1, a+b, '@');
    }
    if (znak == '*') {
        push(top1, a*b , '@');
    }
    if (znak == '/') {
        if (a == 0) {
        sch_apl = -1;
        }
        push(top1, b/a, '@');
    }
    if (znak == 'S') {
        push(top1, sin(a), '@');
    }
    if (znak == 'C') {
        push(top1, cos(a), '@');
    }
    if (znak == 'T') {
        push(top1, tan(a), '@');
    }
    if (znak == '^') {
        push(top1, pow(b,a), '@');
    }
    if (znak == 'K') {
        if (a < 0) {
        sch_apl = -1;
        }
        push(top1, sqrt(a), '@');
    }
    if (znak == 'L') {
        if (a <= 0) {
        sch_apl = -1;
        }
        push(top1, log(a), '@');
    }
}

int Error(string s) {
  int balance = 0;
  for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(') {
          balance++;
      } else if (s[i] == ')') {
          balance--;
      }
      if (balance < 0) {
          return -1;
      }
  }
if (balance != 0) {
    return -1;
}
balance = 0;
if (s[0] == '*' || s[0] == '/' || s[0] == '+') {
    return -1;
}
if (s[s.size()-1] == '*' || s[s.size()-1] == '/' || s[s.size()-1] == '-' || s[s.size()-1] == '+') {
    return -1;
}
for (int i = 0; i <= s.length()- 1; i++) {
    if ((s[i] == '+'|| s[i] == '*' || s[i] == '/' || s[i] == '-')
        && (s[i+1] == '+'|| s[i+1] == '*' || s[i+1] == '/' || s[i+1] == '-')){
       return -1;
    }
}
for (int i = 0; i <= s.length()- 1; i++) {
    if (s[i] == '(' && s[i+ 1] == '*') {
        return -1;
    }
    if (s[i] == '(' && s[i+ 1] == '/') {
        return -1;
    }
    if (s[i] == '(' && s[i+ 1] == '+') {
        return -1;
    }
}
for (int i = 0; i <= s.length()- 1; i++) {
    if (s[i+1] == ')' && s[i] == '*') {
        return -1;
    }
    if (s[i+ 1] == ')' && s[i] == '/') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == '+') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == '-') {
        return -1;
    }
}
for (int i = 0; i <= s.length()- 1; i++) {
    if (s[i]== '/' && s[i+1] == '0'){
        return -1;
    }
}
}

int calc(string s, double &ans) {
    replace_F(s, "S", "sin");
    replace_F(s, "C", "cos");
    replace_F(s, "T", "tg");
    replace_F(s, "K", "sqrt");
    replace_F(s, "L", "ln");
    string ss;
    if (s[0] == '-') {
         s = '0' + s;
    }
    int rr = Error(s);
    if (rr == -1) {
        return -1;
    }
    int balance = 0;
  for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(') {
          balance++;
      } else if (s[i] == ')') {
          balance--;
      }
      if (balance < 0) {
          return -1;
      }
  }
if (balance != 0) {
    return -1;
}
balance = 0;
if (s[0] == '*' || s[0] == '/' || s[0] == '+' || s[0] == '^') {
    return -1;
}
if (s[s.size()-1] == '*' || s[s.size()-1] == '/' || s[s.size()-1] == '-' || s[s.size()-1] == '+' || s[s.size()-1] == '^'){
    return -1;
}
if (s[s.size()-1] == 'S' || s[s.size()-1] == 'C' || s[s.size()-1] == 'T' || s[s.size()-1] == 'K' || s[s.size()-1] == 'L') {
    return -1;
}
for (int i = 0; i <= s.length()- 1; i++) {
    if ((s[i] == '+'|| s[i] == '*' || s[i] == '/' || s[i] == '-')
        && (s[i+1] == '+'|| s[i+1] == '*' || s[i+1] == '/' || s[i+1] == '-')){
       return -1;
    }
}
for (int i = 0; i <= s.length()- 1; i++) {
    if (s[i] == '(' && s[i+ 1] == '*') {
        return -1;
    }
    if (s[i] == '(' && s[i+ 1] == '/') {
        return -1;
    }
    if (s[i] == '(' && s[i+ 1] == '+') {
        return -1;
    }
}
for (int i = 0; i <= s.length()- 1; i++) {
    if (s[i+1] == ')' && s[i] == '*') {
        return -1;
    }
    if (s[i+ 1] == ')' && s[i] == '/') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == '+') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == '-') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == 'S') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == 'C') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == 'T') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == 'K') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == 'L') {
        return -1;
    }
    if (s[i + 1] == ')' && s[i] == '^') {
        return -1;
    }
}
for (int i = 0; i <= s.length()- 1; i++) {
    if (s[i]== '/' && s[i+1] == '0'){
        return -1;
    }
}
    for (int i = 0; i < s.length() - 1; i++) {
        if (s[i] == '(' && s[i+1] == '-') {
            ss = ss + s[i] + '0';
        } else {
            ss = ss + s[i];
            }
        }
        ss += s[s.length()-1];
        s = ss;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            double mnch = 0;
            int ts = 1;
            while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
                if (s[i] >= '0' && s[i] <= '9' && ts == 1) {
                    mnch = mnch*10 + (s[i]-'0');
                    i++;
                }
                if (s[i] == '.') {
                    i++;
                    mnch = mnch + ((s[i]-'0') / pow(10, ts));
                    i++;
                    ts++;
                }
                if (s[i] >= '0' && s[i] <= '9' && ts != 1){
                    mnch = mnch + ((s[i]-'0') / pow(10, ts));
                    i++;
                    ts++;
                }
            }
        i--;
        push(top1, mnch, '@');
        }

        if (s[i] == '(') {
            push(top2, 0, s[i]);
        }
        if (s[i] == ')') {
            while ((*top2).znak != '(') {
                apply(pop(top2).znak);
            }
        pop(top2);
        }
        if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*' || s[i] == '^') {
            while (top2 != nullptr && prior((*top2).znak) >= prior(s[i])) {
                    apply(pop(top2).znak);
                }
            push(top2, 0, s[i]);
        }
        if (s[i] == 'S' || s[i] == 'C' || s[i] == 'T' || s[i] == 'L' || s[i] == 'K') {
            while (top2 != nullptr && prior((*top2).znak) >= prior(s[i])) {
                    apply(pop(top2).znak);
                }
            push(top2, 0, s[i]);
        }
    }

    while (top2 != nullptr) {
       apply(pop(top2).znak);
    }
    ans = pop(top1).number;
    printf("%f", ans);
    if (sch_apl == -1){
        return -1;
    } else {return 0;}
}
