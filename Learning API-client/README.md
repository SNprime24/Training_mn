# GitHub API Client

A JavaScript client for the [GitHub Users REST API](https://docs.github.com/en/rest/users/users) and a small web app to test it.

## Files

- `githubApiClient.js` — `GitHubApiClient` class (Node.js and browser)
- `index.html` — test website
- `app.js` — fetches and displays user data
- `styles.css` — page styling

## Start the website

From the project root, run:

```bash
npx serve "Learning API-client" -l 3456
```

Then open **http://localhost:3456** in your browser, enter a GitHub username (e.g. `octocat`), and click **Search**.

> Use a local server — opening `index.html` directly may block API requests.


## API methods

| Method | Description |
|--------|-------------|
| `getUser(username)` | User profile |
| `getFollowers(username)` | List of followers |
| `getFollowing(username)` | List of users being followed |
| `getRepositories(username)` | Public repositories |
