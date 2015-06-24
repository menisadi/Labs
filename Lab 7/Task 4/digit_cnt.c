int digit_cnt(char *str) {
  int ans = 0, i = 0;
  
  while (str[i] != 0)  {
    if (str[i] >= 48 && str[i] <= 57)
      ans++;
    i++;
  }
  
  return ans;
}

int main(int argc, char **argv) {
    return 0;
}
 
