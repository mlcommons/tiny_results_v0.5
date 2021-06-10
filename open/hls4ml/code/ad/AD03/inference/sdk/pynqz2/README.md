# Boot from Flash

- In the SDK, select `anomaly_detector_fsbl` in _Project Explorer_
- Click: `Xilinx >> Create Boot Image`
- Click: `Add`

<img src="doc/01.png" width=600/>

- Select: `anomaly_detector_standalone`

<img src="doc/02.png" width=600/>

- Click: `Create Image`
- Click: `Xilinx >> Program Flash`
- Click: `Image File:` - `Browse`

<img src="doc/03.png" width=400/>

- Select: `BOOT.bin` (check the full path at the top of the following image)

<img src="doc/04.png" width=600/>

- Click: `Ok`
- Select: `anomaly_detector_fsbl.elf`

<img src="doc/05.png" width=600/>

- Click: `Ok`
- **Make sure that the jumper on the board is on QSPI**
- Click: `Program`
