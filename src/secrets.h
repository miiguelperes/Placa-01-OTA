#ifndef secrets_h
#define secrets_h

// certificate for https://placa-01.herokuapp.com
// Amazon, valid until Wed May 31 2023, size: 2086 bytes 
const char* rootHerokuCACertificate = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIF2DCCBMCgAwIBAgIQCATz5aZZuCN+mpdT+8lWPjANBgkqhkiG9w0BAQsFADBG\n" \
"MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRUwEwYDVQQLEwxTZXJ2ZXIg\n" \
"Q0EgMUIxDzANBgNVBAMTBkFtYXpvbjAeFw0yMjA1MDIwMDAwMDBaFw0yMzA1MzEy\n" \
"MzU5NTlaMBoxGDAWBgNVBAMMDyouaGVyb2t1YXBwLmNvbTCCASIwDQYJKoZIhvcN\n" \
"AQEBBQADggEPADCCAQoCggEBALXDATyDkcy9VxwSm8Q/VidQWsgOYG0Ao5hVzbQo\n" \
"DEfeiCDy+aQUvtv5QLoQQc6LVn9fOGQ4baVxznXh+I4MXhrtE3XTSnBcGjaLXpnW\n" \
"bMsREdECj4D8s+r0sNfeVnypGLB1dq7aHW1FCvNX0kks814vhpZkjd6TkcoPbjJT\n" \
"4VYk3J1dDJdTlEpdmV//WfE0ycnwoT+i6dy1ZZTbtr4lMbbAvMF41VjGjilOPC/V\n" \
"Pz0QqRFFRi3iKtqLhtCyVHlY0hNuGQ4xFtkMLWfvcz0gLYqHudJqB6dtT64bkPZo\n" \
"YvJgju/u7X0csH9MB+Li0Vm/zSHmOhD9i+vVRw0oN6cPoiUCAwEAAaOCAuwwggLo\n" \
"MB8GA1UdIwQYMBaAFFmkZgZSoHuVkjyjlAcnlnRb+T3QMB0GA1UdDgQWBBRL7zjA\n" \
"3rkYN9mT/YlV1MBntn9OYjAaBgNVHREEEzARgg8qLmhlcm9rdWFwcC5jb20wDgYD\n" \
"VR0PAQH/BAQDAgWgMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjA9BgNV\n" \
"HR8ENjA0MDKgMKAuhixodHRwOi8vY3JsLnNjYTFiLmFtYXpvbnRydXN0LmNvbS9z\n" \
"Y2ExYi0xLmNybDATBgNVHSAEDDAKMAgGBmeBDAECATB1BggrBgEFBQcBAQRpMGcw\n" \
"LQYIKwYBBQUHMAGGIWh0dHA6Ly9vY3NwLnNjYTFiLmFtYXpvbnRydXN0LmNvbTA2\n" \
"BggrBgEFBQcwAoYqaHR0cDovL2NydC5zY2ExYi5hbWF6b250cnVzdC5jb20vc2Nh\n" \
"MWIuY3J0MAwGA1UdEwEB/wQCMAAwggGABgorBgEEAdZ5AgQCBIIBcASCAWwBagB3\n" \
"AK33vvp8/xDIi509nB4+GGq0Zyldz7EMJMqFhjTr3IKKAAABgIM4Qu4AAAQDAEgw\n" \
"RgIhAOjMAj1OkAXKATGtmAqt3aEpesRCd4OrT4ZI4sRPbXlIAiEA8be25iwAAOKi\n" \
"J1mPbsCe0FXl3EibQfMBHpjd6wtsH0QAdgA1zxkbv7FsV78PrUxtQsu7ticgJlHq\n" \
"P+Eq76gDwzvWTAAAAYCDOELrAAAEAwBHMEUCIQD+ewe/rjLPHn5DoblKLnOHDPbh\n" \
"ZLmIiZZlbjM6T5eWwwIgTdT/W79MgKKsWO8pg8fx204VXFBeE5BZoU7eC0Z3xP8A\n" \
"dwC3Pvsk35xNunXyOcW6WPRsXfxCz3qfNcSeHQmBJe20mQAAAYCDOELZAAAEAwBI\n" \
"MEYCIQC67zT7hMWLLebemmyAoYnwZrakjjAPdvMjGN51Bfx0IAIhAMhc7Li33Djg\n" \
"sBgQQlHyNlJ3uFeHFsgLLQTDwDElcSR9MA0GCSqGSIb3DQEBCwUAA4IBAQAQUriJ\n" \
"8iCTS+ww8zJeDgGbmzr/EiomNEq+b1s2tzEtTzLkPId1KTfoZvthYOFePWYEWRJ2\n" \
"swHCS6AKsYd47N0ThljkMzY5IzUA2NgwrsRdTk6zCSUIwO692ecf+qmJpUovQRDp\n" \
"xKtUQuy7lhjIeROi1S5cvyxqsfMOWqIF/82O3bArNcwf0E1dHPB/IzRJCDRT/0HW\n" \
"WYI4evDTgBrROC1MJN+eCqPg/MnQ90lCf43Cjdn+X26DXxt4wB7XwFm0EWdW9fKO\n" \
"kL8RPK4/ge4oeR2RNcFKXXlnzuhnWns7/gesxBWTTS8deApbJAMmB7AwX7f9nTPm\n" \
"DL4EkrwdJRHD2U1e\n" \
"-----END CERTIFICATE-----\n" \
"";

char* rootCACertificate = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIEvjCCA6agAwIBAgIQBtjZBNVYQ0b2ii+nVCJ+xDANBgkqhkiG9w0BAQsFADBh\n" \
"MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n" \
"d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n" \
"QTAeFw0yMTA0MTQwMDAwMDBaFw0zMTA0MTMyMzU5NTlaME8xCzAJBgNVBAYTAlVT\n" \
"MRUwEwYDVQQKEwxEaWdpQ2VydCBJbmMxKTAnBgNVBAMTIERpZ2lDZXJ0IFRMUyBS\n" \
"U0EgU0hBMjU2IDIwMjAgQ0ExMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKC\n" \
"AQEAwUuzZUdwvN1PWNvsnO3DZuUfMRNUrUpmRh8sCuxkB+Uu3Ny5CiDt3+PE0J6a\n" \
"qXodgojlEVbbHp9YwlHnLDQNLtKS4VbL8Xlfs7uHyiUDe5pSQWYQYE9XE0nw6Ddn\n" \
"g9/n00tnTCJRpt8OmRDtV1F0JuJ9x8piLhMbfyOIJVNvwTRYAIuE//i+p1hJInuW\n" \
"raKImxW8oHzf6VGo1bDtN+I2tIJLYrVJmuzHZ9bjPvXj1hJeRPG/cUJ9WIQDgLGB\n" \
"Afr5yjK7tI4nhyfFK3TUqNaX3sNk+crOU6JWvHgXjkkDKa77SU+kFbnO8lwZV21r\n" \
"eacroicgE7XQPUDTITAHk+qZ9QIDAQABo4IBgjCCAX4wEgYDVR0TAQH/BAgwBgEB\n" \
"/wIBADAdBgNVHQ4EFgQUt2ui6qiqhIx56rTaD5iyxZV2ufQwHwYDVR0jBBgwFoAU\n" \
"A95QNVbRTLtm8KPiGxvDl7I90VUwDgYDVR0PAQH/BAQDAgGGMB0GA1UdJQQWMBQG\n" \
"CCsGAQUFBwMBBggrBgEFBQcDAjB2BggrBgEFBQcBAQRqMGgwJAYIKwYBBQUHMAGG\n" \
"GGh0dHA6Ly9vY3NwLmRpZ2ljZXJ0LmNvbTBABggrBgEFBQcwAoY0aHR0cDovL2Nh\n" \
"Y2VydHMuZGlnaWNlcnQuY29tL0RpZ2lDZXJ0R2xvYmFsUm9vdENBLmNydDBCBgNV\n" \
"HR8EOzA5MDegNaAzhjFodHRwOi8vY3JsMy5kaWdpY2VydC5jb20vRGlnaUNlcnRH\n" \
"bG9iYWxSb290Q0EuY3JsMD0GA1UdIAQ2MDQwCwYJYIZIAYb9bAIBMAcGBWeBDAEB\n" \
"MAgGBmeBDAECATAIBgZngQwBAgIwCAYGZ4EMAQIDMA0GCSqGSIb3DQEBCwUAA4IB\n" \
"AQCAMs5eC91uWg0Kr+HWhMvAjvqFcO3aXbMM9yt1QP6FCvrzMXi3cEsaiVi6gL3z\n" \
"ax3pfs8LulicWdSQ0/1s/dCYbbdxglvPbQtaCdB73sRD2Cqk3p5BJl+7j5nL3a7h\n" \
"qG+fh/50tx8bIKuxT8b1Z11dmzzp/2n3YWzW2fP9NsarA4h20ksudYbj/NhVfSbC\n" \
"EXffPgK2fPOre3qGNm+499iTcc+G33Mw+nur7SpZyEKEOxEXGlLzyQ4UfaJbcme6\n" \
"ce1XR2bFuAJKZTRei9AqPCCcUZlM51Ke92sRKw2Sfh3oius2FkOH6ipjv3U/697E\n" \
"A7sKPPcw7+uvTPyLNhBzPvOk\n" \
"-----END CERTIFICATE-----\n" \
"";

  // Amazon's root CA. This should be the same for everyone.
  char AWS_CERT_CA[] = "-----BEGIN CERTIFICATE-----\n"
                       "MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"
                       "ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"
                       "b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"
                       "MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"
                       "b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"
                       "ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"
                       "9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"
                       "IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"
                       "VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"
                       "93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"
                       "jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
                       "AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"
                       "A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"
                       "U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"
                       "N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"
                       "o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"
                       "5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"
                       "rqXRfboQnoZsG4q5WTP468SQvvG5\n"
                       "-----END CERTIFICATE-----\n";

  // The private key for your device
  char AWS_CERT_PRIVATE[] = "-----BEGIN RSA PRIVATE KEY-----\n"
                            "MIIEpAIBAAKCAQEAuABe3veOGgDAU9mvDs3vB2e2kdDdpPQQ+Fg+KIbFkbWF9nwQ\n"
                            "caL3PkP1l4TB2mMOprAvxKcGAFMsqJo2cKUOxSlX+1O4lTei5LONfKfq9eq+25CR\n"
                            "QeUWJHVohgy3VI0i9uGydt0No4AHX8Nna4ZcvjBe9xY4xTe5Lat31z4i3pRwdDV9\n"
                            "xZlmVRGzrwMMfW0u5O521T9ZK8l5m7QsvSjnlrKgqsdcucjXOVO5rg5EmD3GMvYA\n"
                            "t5dcv9pPnF6dhdCRbWzdTzC0T1bBea3pswOWSy6Knni/4IyYCyhWNMT/mc+Kwzw+\n"
                            "Q3MqpIij1KmbBiR+oCITQTvgUjIxYiAH6yy/UQIDAQABAoIBACENx/0r4XYgXmxx\n"
                            "tXXmXqMo6W4mZDqmsYm7aGclVsaHImqV/Oo9CUdBNBQlACH4G4CsM9iS3IwgZOxg\n"
                            "z5jKve2DMM/wST9dAEEvVCJpk9bbda/Bt6Zrvd+My9sQ27ovpHFPOB0MNtABRtHY\n"
                            "K3LwbyanT9f5QPeEvBpNLDkZa3AqUci2dbUmG0imF3v6sHVcvmWZbycahsvU6acg\n"
                            "0TTCt2o93oWcbFkY1rSceG1ctEtJ1AnIV5IiH5PuVg0Ou9zilp1K1JScTdnce/cc\n"
                            "eZjqhPbQpcWHlBJkIDp2FsZv+4VZzxn0F0bkxW+hXke85LWOIkLU7znrCqGw7O1k\n"
                            "SKASikECgYEA9CMi7W9YgChArr60KrENdxPfQWq1yNxiAogdcEEiuvhT9K0VZlp1\n"
                            "QQqc73BL4V2IiKA6O0feDGIucY7hKSIlwVkgqvQ3oMUDgZeqfrIOmjwev++ik5yf\n"
                            "CgGG//g+1GFnTbXESk92oTo8t78D+OZsKrxEzVjwEYE/4kH8nKFTTFkCgYEAwPEx\n"
                            "6RXfICxlKa+G6JTgief7YgZHl7IQ6St/azC5WLe9WnAjeHALSjfzoXk/+HaRgcXe\n"
                            "YY2FTpTnmbNc8rZfyGfwkULh4u/5Z4Ks1kiPRAEycKJprPkDZQ7R/wzzuCl7sKyX\n"
                            "hWzdMg7i4CqKNBudG3w0CHXN+zPwGXPqfb3wy7kCgYEAnS4qBJgVcJ1514esU3ge\n"
                            "ZTYEHQfo9eL9rweXfHhTNfE/jF4LUxSWPUPp+jZghD5F80DFfPkuOubTZAVLbcIw\n"
                            "cKVDZQ1K61Ushrjw6hUVVbOzUHumPkcuFbEaC572RKJZciy+reEvTWpDQUHX+t3P\n"
                            "ckw4N8U0+vAuAyvcybMMADECgYEAjJs5VDOsNzYjQw23sydLuzRj7jvFULdju4kH\n"
                            "goYvjIfaZl3ye4Krt5qu4a4LAHbn8zrPpSgNTgcWANzFj9t4UgPtPO8QzuEzUEva\n"
                            "yQ532YdFyu+RM40E/FCgmM5Hjp4slcQxZ/q9+A0BKXvW28KD69PH16KCSd6/ysy+\n"
                            "xoP1R4ECgYB9vv0NTHtwwUpmgJGf+vFnKCUGUIKYTwtATb3X3dkNxHDyheFC3/Dw\n"
                            "8x74wvKrBEYpSWq49USySsj/a4J8Fy/r6UgbBz2VeiF2EoeUqz6/ac+ZWWm/pq7D\n"
                            "MyrsW/5QqrnKZHwjFEQunQ7zJ3aCw5MgO3PkNpOO3TBfJA/wSNjFtQ==\n"
                            "-----END RSA PRIVATE KEY-----\n";

  // The certificate for your device
  char AWS_CERT_CRT[] = "-----BEGIN CERTIFICATE-----\n"
                        "MIIDWjCCAkKgAwIBAgIVAPZaL0SSTS7DaFz85Xh9mspDxOVOMA0GCSqGSIb3DQEB\n"
                        "CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
                        "IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjA0MjAxNTQ1\n"
                        "NTlaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"
                        "dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC4AF7e944aAMBT2a8O\n"
                        "ze8HZ7aR0N2k9BD4WD4ohsWRtYX2fBBxovc+Q/WXhMHaYw6msC/EpwYAUyyomjZw\n"
                        "pQ7FKVf7U7iVN6Lks418p+r16r7bkJFB5RYkdWiGDLdUjSL24bJ23Q2jgAdfw2dr\n"
                        "hly+MF73FjjFN7ktq3fXPiLelHB0NX3FmWZVEbOvAwx9bS7k7nbVP1kryXmbtCy9\n"
                        "KOeWsqCqx1y5yNc5U7muDkSYPcYy9gC3l1y/2k+cXp2F0JFtbN1PMLRPVsF5remz\n"
                        "A5ZLLoqeeL/gjJgLKFY0xP+Zz4rDPD5DcyqkiKPUqZsGJH6gIhNBO+BSMjFiIAfr\n"
                        "LL9RAgMBAAGjYDBeMB8GA1UdIwQYMBaAFPmX1G9HO73xSx0UeeB2Q2PPeVnIMB0G\n"
                        "A1UdDgQWBBTyyrvmjmSPzxfziNyribtv5s73TTAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"
                        "DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEABcEDXJLO9ADCFo6lco9PFAgc\n"
                        "QnxSxvgB0gQyWYohm/o0ctuHDJ3c4RwYqRz17DNFVh3AfXWOzMqyvDX5X4VRVCvM\n"
                        "2jhH3Hg+SPDRfzRE4ozW7Xhnhn1FeqD8i9e48mexFSY7f1Bmzs6W/IoxDx6peuEU\n"
                        "kybeWDvH+XWO0xCOcqXICfifnmHGxV9vhQLsaCtlO6x7Mn+FU6R3WkxtAU8+r15z\n"
                        "daJ1rfqBZbKquiinnnEsjCTC7o2Xq1v+hmg0jeg7LOwkq+xkJtc4PBThpVsjeMbz\n"
                        "jemTJHwo2lG9ouSE59h0Zwhkp8XMQSlOepHgEvFZV9+f9DKfYNFQTCKAwOgZUg==\n"
                        "-----END CERTIFICATE-----\n";


#endif
