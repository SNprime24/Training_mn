const client = new GitHubApiClient();

const form = document.getElementById('search-form');
const usernameInput = document.getElementById('username');
const submitBtn = document.getElementById('submit-btn');
const statusEl = document.getElementById('status');
const resultsEl = document.getElementById('results');

const profileEl = document.getElementById('profile');
const followersTableBody = document.querySelector('#followers-table tbody');
const followingTableBody = document.querySelector('#following-table tbody');
const reposTableBody = document.querySelector('#repos-table tbody');

function showStatus(message, type) {
  statusEl.textContent = message;
  statusEl.className = `status visible ${type}`;
}

function hideStatus() {
  statusEl.className = 'status';
  statusEl.textContent = '';
}

function formatDate(dateString) {
  if (!dateString) return '—';
  return new Date(dateString).toLocaleDateString(undefined, {
    year: 'numeric',
    month: 'short',
    day: 'numeric',
  });
}

function renderProfile(user) {
  profileEl.innerHTML = `
    <img src="${user.avatar_url}" alt="${user.login} avatar" />
    <div class="profile-info">
      <h2>${user.name || user.login}</h2>
      <p class="login">@${user.login}</p>
      <p class="bio">${user.bio || 'No bio provided.'}</p>
      <div class="stats-row">
        <span class="stat-badge">${user.public_repos} repos</span>
        <span class="stat-badge">${user.followers} followers</span>
        <span class="stat-badge">${user.following} following</span>
        <span class="stat-badge">${user.public_gists} gists</span>
        <span class="stat-badge">Joined ${formatDate(user.created_at)}</span>
      </div>
    </div>
  `;
}

function renderTableRows(tbody, rows, columns, emptyMessage) {
  if (!rows.length) {
    tbody.innerHTML = `<tr class="empty-row"><td colspan="${columns}">${emptyMessage}</td></tr>`;
    return;
  }

  tbody.innerHTML = rows
    .map((row) => `<tr>${row.map((cell) => `<td>${cell}</td>`).join('')}</tr>`)
    .join('');
}

function renderFollowers(followers) {
  const rows = followers.map((user) => [
    `<a href="${user.html_url}" target="_blank" rel="noopener">${user.login}</a>`,
    user.type || 'User',
    `<a href="${user.html_url}" target="_blank" rel="noopener">View profile</a>`,
  ]);
  renderTableRows(followersTableBody, rows, 3, 'No followers found.');
}

function renderFollowing(following) {
  const rows = following.map((user) => [
    `<a href="${user.html_url}" target="_blank" rel="noopener">${user.login}</a>`,
    user.type || 'User',
    `<a href="${user.html_url}" target="_blank" rel="noopener">View profile</a>`,
  ]);
  renderTableRows(followingTableBody, rows, 3, 'Not following anyone.');
}

function renderRepositories(repos) {
  const rows = repos.map((repo) => [
    `<a href="${repo.html_url}" target="_blank" rel="noopener">${repo.name}</a>`,
    repo.description || '—',
    repo.language || '—',
    repo.stargazers_count,
    repo.forks_count,
    repo.private ? 'Private' : 'Public',
    formatDate(repo.updated_at),
  ]);
  renderTableRows(reposTableBody, rows, 7, 'No public repositories found.');
}

async function loadUserData(username) {
  const trimmed = username.trim();
  if (!trimmed) {
    showStatus('Please enter a GitHub username.', 'error');
    return;
  }

  submitBtn.disabled = true;
  resultsEl.classList.remove('visible');
  showStatus(`Fetching data for "${trimmed}"…`, 'loading');

  try {
    const [user, followers, following, repos] = await Promise.all([
      client.getUser(trimmed),
      client.getFollowers(trimmed),
      client.getFollowing(trimmed),
      client.getRepositories(trimmed),
    ]);

    renderProfile(user);
    renderFollowers(followers);
    renderFollowing(following);
    renderRepositories(repos);

    hideStatus();
    resultsEl.classList.add('visible');
  } catch (error) {
    showStatus(error.message || 'Failed to fetch user data.', 'error');
  } finally {
    submitBtn.disabled = false;
  }
}

form.addEventListener('submit', (event) => {
  event.preventDefault();
  loadUserData(usernameInput.value);
});
