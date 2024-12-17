# Zenith Engine Resource Packer Tool
`ZenithPacker` is a command-line tool that packages all assets specified in the `resources.yaml` file into binary asset packages.

## Usage
It is very simple to use ZenithPacker tool. All you need is specify directory that containing the resources.yaml file (which is also the root of the assets folder) and optionally an output directory for packages. If you do not specify an output directory, the output directory will be _${input_directory}/out_ as default. Input directory is mandatory.

### Arguments:
* `-i`, `--i`, `-in`, `--in`: Specifies the input directory.
* `-o`, `--o`, `-out`, `--out`: Specifies the output directory.

### Examples:
```bash
ZenithPacker.exe -i D:/dev/ZenithEngine/Demos/FlappyBird/res
```
```bash
ZenithPacker.exe -i FlappyBird/res -o FlappyBird/build
```

---

## Output Packages
All package files are binary files with `.bin` extension. Actually, the packer, merge resource files of the same kind. And saves required data to load specific asset from package into a binary manifest file (`resources.bin`)

The `resources.bin` file forms of two sections: **header** and **body**.
* The **header section** contains the file format version and total asset count. 
* The **body section** contain metadata of all imported assets. This metadata includes
  *  Asset UUID
  *  Asset Size in Bytes
  *  Offset in the Package
  *  Package File Index
  *  Asset Type

**Note:** An asset's offset value cannot exceed 4,294,967,295 bytes (4 GB) because the offset value is stored in 32-bit unsigned integer variable. If the offset is about to exceed this limit when packing, the current package file is finalized and the packer begis packing the remaining assets into another package file. Hence, the offset value stays within limits and the file index value is incremented.

#### Output Folder Structure:
```
/audio
    audiopack0.bin
    audiopack1.bin
/fonts
    fontpack0.bin
textures/
    texturepack0.bin
    texturepack1.bin
    texturepack2.bin
    texturepack3.bin
resources.bin
```

---

## resources.yaml Format
The `resources.yaml` file is found in the root of the assets folder of the ZenithEngine project and contains metadata of imported assets.

#### General Format:
``` yaml
version: RESOURCES_YAML_FORMAT_VERSION
ASSET_TYPE:
  ASSET_UUID:
    file: ASSET_PATH
```
#### Example File:
```yaml
version: 0.0.1

audio_assets:
  5ad080298809b2bd:
    file: audio/die.ogg
  c0130269e70e98d3:
    file: audio/hit.ogg
  509a52709632374a:
    file: audio/theme.mp3

font_assets:
  a58073b270903d7b:
    file: fonts/Righteous.ttf
    
texture2d_assets:
    file: sprites/yellowbird-downflap.png
  e6a0c985dc320242:
    file: sprites/yellowbird-midflap.png
  4525d381b15851fb:
    file: sprites/yellowbird-upflap.png
        
```
