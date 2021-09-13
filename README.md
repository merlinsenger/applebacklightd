# applebacklightd
Linux daemon for controlling the Apple iMac's display back light

Run manually i.e.

```
$ ./applebacklightd
```

or install by copying to i.e. /usr/local/bin and create a systemd configuration, i.e.

```
merlin@imac:~/git$ cat /etc/systemd/system/applebacklightd.service
[Unit]
Description=Apple display backlight brightness daemon

[Service]
Type=simple
ExecStart=/usr/local/bin/applebacklightd

[Install]
WantedBy=multi-user.target
```

```
$ systemctl start applefand.service
$ systemctl enable applefand.service
```

Check the status using

```
$ systemctl status applebacklightd.service

applebacklightd.service - Apple display backlight brightness daemon
     Loaded: loaded (/etc/systemd/system/applebacklightd.service; enabled; vendor preset: enabled)
     Active: active (running) since Mon 2021-09-13 11:32:59 CEST; 28min ago
   Main PID: 1078 (applebacklightd)
      Tasks: 1 (limit: 19097)
     Memory: 752.0K
     CGroup: /system.slice/applebacklightd.service
             └─1078 /usr/local/bin/applebacklightd

Sep 13 11:32:59 imac systemd[1]: Started Apple display backlight brightness daemon.
```
