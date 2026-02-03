# Release Checklist

## Pre-Release
- [ ] Update version in `package.json` and `CHANGELOG.md`
- [ ] Merge latest `main` into release branch
- [ ] Confirm environment variables are set for production (API URL, monitoring keys)

## Quality Gates
- [ ] `npm run lint`
- [ ] `npm run test -- --watch=false --browsers=ChromeHeadless`
- [ ] `npm run build -- --configuration production`
- [ ] `npm run e2e`
- [ ] Lighthouse audit (Performance ≥ 90, Accessibility ≥ 95)

## Deployment
- [ ] Trigger CI/CD pipeline or deploy manually (`ng deploy`)
- [ ] Verify SSR output renders expected HTML
- [ ] Validate service worker registration and offline cache
- [ ] Smoke test critical flows (login, CRUD, dashboards)

## Post-Release
- [ ] Monitor error/analytics dashboards for anomalies
- [ ] Announce release (Slack/email) with highlights
- [ ] Create follow-up tickets for deferred items
