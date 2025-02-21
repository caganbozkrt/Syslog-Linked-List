Syslog Linked List

Bu proje, Linux işletim sisteminde sistem günlüklerini (syslog) okuyan ve verileri bağlı liste (linked list) veri yapısı kullanarak saklayan bir C programıdır. Program, /var/log/syslog dosyasını okuyarak günlükleri bellekte saklar ve belirli bir günlük seviyesine göre filtreleme yaparak ekrana yazdırır.

Özellikler

Günlükleri Okuma: /var/log/syslog dosyasından satır satır okur.

Bağlı Liste Kullanımı: Günlükleri dinamik olarak bağlı listeye ekler.

Filtreleme: Belirtilen günlük seviyesine göre (örneğin, ERROR) filtreleme yaparak ilgili günlükleri ekrana yazdırır.

Bellek Yönetimi: Kullanılan belleği serbest bırakmak için fonksiyon içerir.
