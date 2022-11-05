#define buzzer 23
#define button2 32
#define button 18
#define ldr 15
#define led_red 27
#define led_green 14
#define led_blue 12
#define led_yellow 13

int binarios[4];
int binarios_convertidos = 0;
int valores_freq_guardados[1000];
int proximo_index = 0;
int ordem_crescente = 0;

void conversao(int valor_da_luz) {
  while (binarios_convertidos != 4) {
    binarios[binarios_convertidos] = valor_da_luz % 2;
    valor_da_luz = valor_da_luz / 2;
    binarios_convertidos ++;
  }

  binarios_convertidos = 0;
}


void acende_led() {

  if (binarios[0] == 1) {
    digitalWrite(led_red, HIGH);
  } else {
    digitalWrite(led_red, LOW);
  }

  if (binarios[1] == 1) {
    digitalWrite(led_green, HIGH);
  } else {
    digitalWrite(led_green, LOW);
  }

  if (binarios[2] == 1) {
    digitalWrite(led_yellow, HIGH);
  } else {
    digitalWrite(led_yellow, LOW);
  }

  if (binarios[3] == 1) {
    digitalWrite(led_blue, HIGH);
  } else {
    digitalWrite(led_blue, LOW);
  }
}

void guarda_frequencia(int inteiro) {
  valores_freq_guardados[proximo_index] = inteiro;
  proximo_index += 1;
  tone(buzzer, inteiro * 100, 200);
}

void tocar_musica() {

  Serial.println(proximo_index);
  while(ordem_crescente < proximo_index ) {
    tone(buzzer, valores_freq_guardados[ordem_crescente]*100, 200);
    ordem_crescente  += 1;
    Serial.println(ordem_crescente);
    conversao(valores_freq_guardados[ordem_crescente]);
    acende_led();
    delay(800);
  }

}
void setup() {
  Serial.begin(115200);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(ldr, INPUT);
  pinMode(buzzer, OUTPUT);
}


void loop() {

  int luz = analogRead(ldr);
  int decimal_luz = (luz/269);

  conversao(decimal_luz);

  if (digitalRead(button) == LOW) {
    acende_led();
    guarda_frequencia(decimal_luz);
  }
  delay(200);

  if (digitalRead(button2) == LOW) {
    tocar_musica();
  }
  delay(200);
}
