class GitHubApiClient {
  constructor(baseUrl = 'https://api.github.com') {
    this.baseUrl = baseUrl.replace(/\/$/, '');
  }

  async _request(path) {
    const response = await fetch(`${this.baseUrl}${path}`);

    if (!response.ok) {
      let message = `HTTP ${response.status} ${response.statusText}`;
      try {
        const errorBody = await response.json();
        if (errorBody.message) {
          message = `${message}: ${errorBody.message}`;
        }
      } catch {
        // Response body is not JSON; keep the default message.
      }
      throw new Error(message);
    }

    return response.json();
  }

  async getUser(username) {
    return this._request(`/users/${encodeURIComponent(username)}`);
  }

  async getFollowers(username) {
    return this._request(`/users/${encodeURIComponent(username)}/followers`);
  }

  async getFollowing(username) {
    return this._request(`/users/${encodeURIComponent(username)}/following`);
  }

  async getRepositories(username) {
    return this._request(`/users/${encodeURIComponent(username)}/repos`);
  }
}

if (typeof module !== 'undefined' && module.exports) {
  module.exports = GitHubApiClient;
} else {
  window.GitHubApiClient = GitHubApiClient;
}
