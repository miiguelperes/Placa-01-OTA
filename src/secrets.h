#ifndef secrets_h
#define secrets_h

// Amazon's root CA. This should be the same for everyone.
const char AWS_CERT_CA[] = "-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n" \
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n" \
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n" \
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n" \
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n" \
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n" \
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n" \
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n" \
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n" \
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n" \
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n" \
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n" \
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n" \
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n" \
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n" \
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n" \
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n" \
"rqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----\n";

// The private key for your device
const char AWS_CERT_PRIVATE[] = "-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEpAIBAAKCAQEAuABe3veOGgDAU9mvDs3vB2e2kdDdpPQQ+Fg+KIbFkbWF9nwQ\n" \
"caL3PkP1l4TB2mMOprAvxKcGAFMsqJo2cKUOxSlX+1O4lTei5LONfKfq9eq+25CR\n" \
"QeUWJHVohgy3VI0i9uGydt0No4AHX8Nna4ZcvjBe9xY4xTe5Lat31z4i3pRwdDV9\n" \
"xZlmVRGzrwMMfW0u5O521T9ZK8l5m7QsvSjnlrKgqsdcucjXOVO5rg5EmD3GMvYA\n" \
"t5dcv9pPnF6dhdCRbWzdTzC0T1bBea3pswOWSy6Knni/4IyYCyhWNMT/mc+Kwzw+\n" \
"Q3MqpIij1KmbBiR+oCITQTvgUjIxYiAH6yy/UQIDAQABAoIBACENx/0r4XYgXmxx\n" \
"tXXmXqMo6W4mZDqmsYm7aGclVsaHImqV/Oo9CUdBNBQlACH4G4CsM9iS3IwgZOxg\n" \
"z5jKve2DMM/wST9dAEEvVCJpk9bbda/Bt6Zrvd+My9sQ27ovpHFPOB0MNtABRtHY\n" \
"K3LwbyanT9f5QPeEvBpNLDkZa3AqUci2dbUmG0imF3v6sHVcvmWZbycahsvU6acg\n" \
"0TTCt2o93oWcbFkY1rSceG1ctEtJ1AnIV5IiH5PuVg0Ou9zilp1K1JScTdnce/cc\n" \
"eZjqhPbQpcWHlBJkIDp2FsZv+4VZzxn0F0bkxW+hXke85LWOIkLU7znrCqGw7O1k\n" \
"SKASikECgYEA9CMi7W9YgChArr60KrENdxPfQWq1yNxiAogdcEEiuvhT9K0VZlp1\n" \
"QQqc73BL4V2IiKA6O0feDGIucY7hKSIlwVkgqvQ3oMUDgZeqfrIOmjwev++ik5yf\n" \
"CgGG//g+1GFnTbXESk92oTo8t78D+OZsKrxEzVjwEYE/4kH8nKFTTFkCgYEAwPEx\n" \
"6RXfICxlKa+G6JTgief7YgZHl7IQ6St/azC5WLe9WnAjeHALSjfzoXk/+HaRgcXe\n" \
"YY2FTpTnmbNc8rZfyGfwkULh4u/5Z4Ks1kiPRAEycKJprPkDZQ7R/wzzuCl7sKyX\n" \
"hWzdMg7i4CqKNBudG3w0CHXN+zPwGXPqfb3wy7kCgYEAnS4qBJgVcJ1514esU3ge\n" \
"ZTYEHQfo9eL9rweXfHhTNfE/jF4LUxSWPUPp+jZghD5F80DFfPkuOubTZAVLbcIw\n" \
"cKVDZQ1K61Ushrjw6hUVVbOzUHumPkcuFbEaC572RKJZciy+reEvTWpDQUHX+t3P\n" \
"ckw4N8U0+vAuAyvcybMMADECgYEAjJs5VDOsNzYjQw23sydLuzRj7jvFULdju4kH\n" \
"goYvjIfaZl3ye4Krt5qu4a4LAHbn8zrPpSgNTgcWANzFj9t4UgPtPO8QzuEzUEva\n" \
"yQ532YdFyu+RM40E/FCgmM5Hjp4slcQxZ/q9+A0BKXvW28KD69PH16KCSd6/ysy+\n" \
"xoP1R4ECgYB9vv0NTHtwwUpmgJGf+vFnKCUGUIKYTwtATb3X3dkNxHDyheFC3/Dw\n" \
"8x74wvKrBEYpSWq49USySsj/a4J8Fy/r6UgbBz2VeiF2EoeUqz6/ac+ZWWm/pq7D\n" \
"MyrsW/5QqrnKZHwjFEQunQ7zJ3aCw5MgO3PkNpOO3TBfJA/wSNjFtQ==\n" \
"-----END RSA PRIVATE KEY-----\n";



// The certificate for your device
const char AWS_CERT_CRT[] = "-----BEGIN CERTIFICATE-----\n" \
"MIIDWjCCAkKgAwIBAgIVAPZaL0SSTS7DaFz85Xh9mspDxOVOMA0GCSqGSIb3DQEB\n" \
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n" \
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA0MjAxNTQ1\n" \
"NTlaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n" \
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC4AF7e944aAMBT2a8O\n" \
"ze8HZ7aR0N2k9BD4WD4ohsWRtYX2fBBxovc+Q/WXhMHaYw6msC/EpwYAUyyomjZw\n" \
"pQ7FKVf7U7iVN6Lks418p+r16r7bkJFB5RYkdWiGDLdUjSL24bJ23Q2jgAdfw2dr\n" \
"hly+MF73FjjFN7ktq3fXPiLelHB0NX3FmWZVEbOvAwx9bS7k7nbVP1kryXmbtCy9\n" \
"KOeWsqCqx1y5yNc5U7muDkSYPcYy9gC3l1y/2k+cXp2F0JFtbN1PMLRPVsF5remz\n" \
"A5ZLLoqeeL/gjJgLKFY0xP+Zz4rDPD5DcyqkiKPUqZsGJH6gIhNBO+BSMjFiIAfr\n" \
"LL9RAgMBAAGjYDBeMB8GA1UdIwQYMBaAFPmX1G9HO73xSx0UeeB2Q2PPeVnIMB0G\n" \
"A1UdDgQWBBTyyrvmjmSPzxfziNyribtv5s73TTAMBgNVHRMBAf8EAjAAMA4GA1Ud\n" \
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEABcEDXJLO9ADCFo6lco9PFAgc\n" \
"QnxSxvgB0gQyWYohm/o0ctuHDJ3c4RwYqRz17DNFVh3AfXWOzMqyvDX5X4VRVCvM\n" \
"2jhH3Hg+SPDRfzRE4ozW7Xhnhn1FeqD8i9e48mexFSY7f1Bmzs6W/IoxDx6peuEU\n" \
"kybeWDvH+XWO0xCOcqXICfifnmHGxV9vhQLsaCtlO6x7Mn+FU6R3WkxtAU8+r15z\n" \
"daJ1rfqBZbKquiinnnEsjCTC7o2Xq1v+hmg0jeg7LOwkq+xkJtc4PBThpVsjeMbz\n" \
"jemTJHwo2lG9ouSE59h0Zwhkp8XMQSlOepHgEvFZV9+f9DKfYNFQTCKAwOgZUg==\n" \
"-----END CERTIFICATE-----\n";






#endif