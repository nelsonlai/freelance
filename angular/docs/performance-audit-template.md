# Performance Audit Template

## Context
- **Route / Scenario Tested**: 
- **Build Configuration**: (`ng build --configuration production`)
- **Device / Network Profile**: (e.g., Lighthouse Mobile, 4x CPU slowdown)
- **Date**: 

## Lighthouse Summary
| Metric | Baseline | Optimized | Delta |
| --- | --- | --- | --- |
| Performance |  |  |  |
| Accessibility |  |  |  |
| Best Practices |  |  |  |
| SEO |  |  |  |

## Web Vitals
- **LCP**: 
- **FID/INP**: 
- **CLS**: 
- **TTFB**: 

## Observed Bottlenecks
- `[]` Unused JavaScript / CSS
- `[]` Large hero image unoptimized
- `[]` Excessive change detection cycles
- `[]` Blocking third-party scripts
- Additional notes:

## Optimization Actions
1. 
2. 
3. 

## Verification
- [ ] Re-run Lighthouse after optimizations
- [ ] Validate change detection with Angular DevTools profiler
- [ ] Confirm bundle budgets pass (`ng build` output)
- [ ] Run E2E smoke tests with service worker enabled

## Follow-up Tasks
- 
- 
