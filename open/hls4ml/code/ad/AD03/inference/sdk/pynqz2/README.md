# Boot from Flash

- In the SDK, select `anomaly_detector_fsbl` in _Project Explorer_
- Click: `Xilinx >> Create Boot Image`
- Click: `Add`

![doc/01.png](doc/01.png)

- Select: `anomaly_detector_standalone`

![doc/02.png](doc/02.png)

- Click: `Create Image`
- Click: `Xilinx >> Program Flash`
- Click: `Image File:` - `Browse`

![doc/03.png](doc/03.png)

- Select: `BOOT.bin` (check the full path at the top of the following image)

![doc/04.png](doc/04.png)

- Click: `Ok`
- Select: `anomaly_detector_fsbl.elf`

![doc/05.png](doc/05.png)

- Click: `Ok`
- **Make sure that the jumper on the board is on QSPI**
- Click: `Program`
