# Claude AI Development Reference

This file provides quick reference for AI assistants working on the RotaryEncoder ESP32 library project.

## Project Overview

A high-performance rotary encoder library for ESP32 microcontrollers with the following key features:
- Template-based design supporting multiple encoders simultaneously  
- Interrupt-driven operation for responsive performance
- Detent filtering with configurable counts per detent (default 4 for PEC11)
- Thread-safe value reading with atomic operations
- Optional debug output via callback functions

## Repository Structure

```
rotary-encoder-esp32/
├── src/
│   ├── RotaryEncoder.h       # Main header with class definition
│   └── RotaryEncoder.tpp     # Template implementation
├── examples/
│   └── basic_usage/          # Working example project
├── library.json             # PlatformIO library manifest
├── library.properties       # Arduino IDE compatibility
├── README.md                # Comprehensive documentation
├── LICENSE                  # MIT license
└── keywords.txt             # Arduino IDE syntax highlighting
```

## Key Technical Details

### Template Design
- Uses template parameter `<int ID>` for unique encoder identification
- Static member `instance` for ISR callback handling
- Each template instantiation creates separate static variables

### Hardware Support
- **Primary target**: PEC11 rotary encoders
- **Counts per detent**: 4 (standard for PEC11), configurable
- **Pin requirements**: Two GPIO pins for A/B signals, optional third for push button
- **Internal pullups**: Enabled automatically, external pullups optional

### API Design Philosophy
- **Minimal overhead**: Template-based eliminates runtime polymorphism costs
- **Safety first**: Thread-safe getValue() with interrupt protection
- **Flexibility**: Optional debug callback instead of hardcoded Serial output
- **ESP32 optimized**: Uses ESP32-specific interrupt handling

## Development Guidelines

### Making Changes
1. **Test thoroughly**: Library is used in production projects
2. **Maintain backward compatibility**: Avoid breaking API changes
3. **Update version**: Increment version in `library.json` for releases
4. **Test example**: Ensure `examples/basic_usage` still works
5. **Update documentation**: Keep README.md current with API changes

### Common Tasks

#### Version Release
```bash
# Update library.json version
# Tag release
git tag v1.1.0
git push origin v1.1.0
```

#### Testing Changes
```bash
# Test with example
cd examples/basic_usage
pio run --environment esp32-c6-devkitc-1

# Test in dependent projects
# Update lib_deps to use local path temporarily:
# lib_deps = file://../../rotary-encoder-esp32
```

#### Adding New Features
- Consider impact on template instantiation overhead
- Maintain interrupt-safe design
- Add corresponding example usage
- Document in README.md

## Library Manifest Key Fields

From `library.json`:
- **name**: "RotaryEncoder ESP32"
- **platforms**: ["espressif32"] 
- **frameworks**: ["arduino"]
- **headers**: ["RotaryEncoder.h"]

## Known Integration Points

### Used By
- **linea-micra-controller**: Main consumer project
- Template ID 0: Primary encoder on pins 0, 20

### Dependencies
- **Arduino framework**: Core GPIO and interrupt functions
- **No external libraries**: Self-contained implementation

## Troubleshooting Notes

### Common Issues
1. **Multiple encoder conflicts**: Ensure unique template IDs
2. **Erratic readings**: Check wiring, add hardware debouncing capacitors
3. **Build errors**: Verify ESP32 platform and Arduino framework versions

### Debug Strategies
- Use debug callback to verify initialization
- Monitor raw _value vs processed value in ISR
- Check interrupt attachment success

## Future Enhancement Ideas

- [ ] Add support for push button functionality
- [ ] Implement acceleration/velocity detection
- [ ] Add configuration for different encoder types (EC11, etc.)
- [ ] Support for encoders with different pulse counts per detent
- [ ] Optional EEPROM position persistence
- [ ] Direction reversal configuration

## Maintenance Reminders

- **Test compatibility** with new ESP32-Arduino core releases
- **Review performance** with newer ESP32 variants (S2, S3, C3, etc.)
- **Monitor GitHub issues** from users
- **Consider PlatformIO registry** submission for broader distribution

---

*Last updated: 2025-01-13*  
*Initial creation during library extraction from linea-micra-controller*