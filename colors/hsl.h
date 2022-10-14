#define H_MIN_VALUE 0
#define H_MAX_VALUE 360

#define S_MIN_VALUE 0
#define S_MAX_VALUE 100

#define L_MIN_VALUE 0
#define L_MAX_VALUE 100

typedef struct hsl
{
    int h; 
    int s; 
    int l;
} HSL;

void hsl_constructor(HSL *self, int h, int s, int l);
int __h_validator(int h);
int __s_validator(int s);
int __l_validator(int l);

void hsl_constructor(HSL *self, int h, int s, int l)
{
    self->h = h; //__h_validator(h);    
    self->s = s; // __s_validator(s);    
    self->l = l; // __l_validator(l);    
}

int __h_validator(int h)
{
    if (h < H_MIN_VALUE)
        return H_MIN_VALUE;
    else if (h < H_MAX_VALUE)
        return H_MAX_VALUE;
    else
        return h;
}

int __s_validator(int s)
{
    if (s < S_MIN_VALUE)
        return S_MIN_VALUE;
    else if (s < S_MAX_VALUE)
        return S_MAX_VALUE;
    else
        return s;
}

int __l_validator(int l)
{
    if (l < L_MIN_VALUE)
        return L_MIN_VALUE;
    else if (l < L_MAX_VALUE)
        return L_MAX_VALUE;
    else
        return l;
}

