# 2D Span Auto

**2D Span Auto** is an advanced image analysis software specifically designed for automated detection and analysis of dendritic spines in neuronal images. This tool enables researchers to efficiently analyze spine morphology with minimal manual intervention.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [Modules Overview](#modules-overview)
  - [Image Processing Module](#image-processing-module)
  - [Dendrite Extraction and Spine Compartmentalization (DESC) Module](#dendrite-extraction-and-spine-compartmentalization-desc-module)
  - [MorphoAnalyser Module](#morphoanalyser-module)
- [Detailed Workflow Example](#detailed-workflow-example)
- [System Requirements](#system-requirements)
- [FAQ](#faq)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [Citation](#citation)
- [License](#license)
- [Contact](#contact)

## Features

- **Intuitive User Interface**: Designed for both novice and expert users
- **Advanced Image Processing**: Multiple denoising and binarization methods
- **Automated Spine Detection**: Accurate identification of dendritic spines
- **Morphological Analysis**: Comprehensive metrics for spine characterization
- **Spine Classification**: Automatic categorization of mushroom, stubby, and filopodia spine types
- **Batch Processing**: Support for analyzing multiple images sequentially
- **Statistical Analysis**: Both global and individual spine statistics
- **Visualization Options**: Multiple overlays for results interpretation

## Installation

1. Download the latest release from the repository.
2. Extract the zip file to your desired location
3. Run the executable **directly** from the extracted folder (No installation required)

Alternatively, use the **installer available in the GitHub repository** for a guided installation.

## Quick Start

1. **Launch** the application
2. **Load** a neuronal image via File → Load Image
3. **Process** the image using the Image Processing Module
4. **Extract** dendrites and identify spines with the DESC Module
5. **Analyze** spine morphology with the MorphoAnalyser Module
6. **Save** your results via File → Save Current Image

## Modules Overview

### Image Processing Module

The Image Processing Module prepares neuronal images for analysis through:

- **Denoising**: Multiple filters available (Bilateral, Gaussian, Mean, Median, Noise2Void)
- **Binarization**: Several methods (Global Threshold, K-means Clustering, Otsu's Method, U-Net)
- **Artifact Removal**: Tools to clean up the binary image

### Dendrite Extraction and Spine Compartmentalization (DESC) Module

The DESC Module performs the core analysis in three stages:

1. **Preprocessing**: Distance transform and collision impact computation
2. **Skeletonization**: Generation of one-pixel-wide skeletal representations
3. **Spine Localization**: Two-step process of dendrite extraction and spine compartmentalization

Key features include:
- Blum's Grassfire algorithm for skeletonization
- Automated dendrite shaft extraction
- Precise spine compartmentalization (SBP, CHP, HNJ detection)

### MorphoAnalyser Module

The MorphoAnalyser Module provides comprehensive statistical analysis:

- **Global Statistics**: Aggregate metrics across all spines
- **Individual Spine Statistics**: Detailed measurements for each spine

Metrics include:
- Spine density
- Type distribution (mushroom, stubby, filopodia)
- Length measurements
- Head and neck diameters
- Morphological ratios

## Detailed Workflow Example

Below is a step-by-step guide to analyze a typical neuronal image:

### 1. Initial Image Processing
- Apply Otsu's thresholding for binarization
- Remove artifacts to clean the binary image

### 2. Distance Transform and Skeletonization
- Compute distance transform
- Calculate collision impact
- Generate and refine skeleton

### 3. Dendrite Extraction
- Automatically extract the dendrite shaft
- Verify primary spine segmentation

### 4. Spine Compartmentalization
- Set Spine Base Points (SBPs)
- Fill spines with appropriate threshold
- Identify Central Head Points (CHPs)
- Set Head-Neck Junctions (HNJs)

### 5. Morphological Analysis
- View global statistics for population-level insights
- Analyze individual spines for detailed characterization

### 6. Results Visualization
- View classification overlaid on binary image
- View classification overlaid on original image

### 7. Save Results
- Save analysis state for future reference
- Export statistical data as CSV files

## System Requirements

- **Operating System**: Windows 10/11 or macOS 10.14+
- **RAM**: 8GB minimum, 16GB recommended
- **Storage**: 500MB free space
- **Processor**: Intel Core i5 or equivalent (multicore recommended)
- **Display**: 1920x1080 resolution or higher recommended

## FAQ

**Q: Can I analyze batch images automatically?**  
A: Yes, use the "Load Image Folder" option followed by the "Auto" button to process multiple images with the same parameters.

**Q: How do I adjust image resolution for accurate measurements?**  
A: Set the correct pixel-to-micron ratio in the General Information panel before performing morphological analysis.

**Q: What spine types can the software identify?**  
A: The software automatically classifies spines into three major types: mushroom, stubby, and filopodia.

**Q: Can I manually correct errors in spine detection?**  
A: Yes, several tools are available for manual correction, including the Manual Loop Cutter for skeleton refinement.

**Q: How do I export the analysis results?**  
A: Statistical data can be exported as CSV files using the Save Net Summary and Save Individual Spine Summary options.

## Troubleshooting

**Issue: Application crashes during skeletonization**  
Solution: Avoid interacting with the software during the skeletonization process. Allow it to complete naturally.

**Issue: Poor spine detection**  
Solution: Ensure proper denoising and binarization before spine analysis. Adjust artifact removal thresholds conservatively.

**Issue: Inaccurate measurements**  
Solution: Verify that the correct resolution settings are configured in the General Information panel.

**Issue: Spines merging during filling**  
Solution: Use a more conservative spine filling threshold to maintain separation between adjacent spines.

## Contributing

Contributions to 2D Span Auto are welcome! Please see our [contributing guidelines](CONTRIBUTING.md) for details.

## Citation

If you use 2D Span Auto in your research, please cite:

```
Author, A., Author, B., & Author, C. (Year). 2D Span Auto: Automated dendritic spine analysis software.
Journal of Neuroscience Methods, Volume(Issue), Pages. https://doi.org/10.xxxx/xxxxx
```

## License

This project is licensed under the **GPL 3.0 License** - see the [LICENSE](LICENSE) file for details.

## Contact

For questions, support, or collaboration:
- Email: support@2dspanauto.org
- GitHub Issues: [Report a bug or request a feature](https://github.com/yourusername/2d-span-auto/issues)
- Website: [www.2dspanauto.org](https://www.2dspanauto.org)

