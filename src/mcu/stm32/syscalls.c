int _init(void) {
  return 0;
}

int _close(int file) {
  return -1;
}
int _lseek(int file, int ptr, int dir) {
  return 0;
}

int _read (int file, char * ptr, int len) {
  int read = 0;
/*
  if (file != 0) {
    return -1;
  }

  for (; len > 0; --len) {
    usart_serial_getchar(&stdio_uart_module, (uint8_t *)ptr++);
    read++;
  }*/
  return read;
}
int _write (int file, char * ptr, int len) {
  int written = 0;
/*
  if ((file != 1) && (file != 2) && (file != 3)) {
    return -1;
  }

  for (; len != 0; --len) {
    if (usart_serial_putchar(&stdio_uart_module, (uint8_t)*ptr++)) {
      return -1;
    }
    ++written;
  }*/
  return written;
}